/*
 * dns.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dnsmuncher/config.h"
#include "dnsmuncher/util/logging.h"
#include "dnsmuncher/dns.h"
#include "dnsmuncher/actors/data_producer.h"
#include "dnsmuncher/data/dns_convert.h"
#include "dnsmuncher/domain/dns.h"
#include "dnsmuncher/actors/dns_response_consumer.h"
#include "dnsmuncher/domain/resource_record_all.h"
#include "dnsmuncher/domain/dns_builder.h"
#include "dnsmuncher/socket/socket.h"
#include "dnsmuncher/parse/ip.h"
#include "dnsmuncher/util/collection.h"
#include <boost/bind.hpp>
#include <string>
#include <iostream>

// Runs a consumer and deletes it after completion.
void socket_thread_runner(int fd, boost::shared_ptr<Consumer> c) {
	c->run(fd);
#ifdef LOGGING
	LOG(INFO) << "Thread finalizing";
#endif

#ifdef LOGGING
	LOG(INFO) << "Releasing resources";
#endif
	c.reset();

#ifdef LOGGING
	LOG(INFO) << "Closing spawned socket(not the listening one)";
#endif
	// No need to close socket with new Socket class
	//close_socket(fd);
#ifdef LOGGING
	LOG(INFO) << "Thread released";
#endif
}

typedef boost::function< boost::optional<std::string> ( DNS::ResourcePtr ) > FilterFunction;

std::vector<std::string> filter_resource_by_type( DnsPtr query, Type t, FilterFunction f ) {
	std::vector<std::string> results;
	if( query->response_code() == DNS::NO_ERROR ) {
		DNS::ResourceList resources  = query->get_resource_records();
		if( !resources.empty()) {
			for( size_t i = 0; i < resources.size(); ++i ) {
				if( resources.at(i)->get_type() == t ) {
					boost::optional<std::string> result = f( resources.at(i) );
					if( result ) {
						results.push_back( *result );
					}
				}
			}
		}
	}
	return results;
}

boost::optional<std::string> ip_filter_function( DNS::ResourcePtr resource ) {
#ifdef LOGGING
	LOG(INFO) << "Interpreting as ips";
#endif
	return ip_from_data( resource->get_data() );
}

std::vector<std::string> filter_ips( DnsPtr query ) {
	return filter_resource_by_type( query, Type::A, &ip_filter_function );
}

boost::optional<std::string> filter_first_ip( DnsPtr query ) {
	return maybe_first( filter_ips( query ) );
}

boost::optional<std::string> ns_filter_function( DNS::ResourcePtr resource ) {
#ifdef LOGGING
	LOG(INFO) << "Interpreting as ns";
#endif
	boost::optional<std::string> ns;
	boost::shared_ptr<NsResourceRecord> casted = boost::dynamic_pointer_cast<NsResourceRecord>(resource);
	if( casted ) {
		ns = casted->get_name().to_string();
	}
#ifdef LOGGING
	else {
		LOG(WARNING) << "Could not interpret record as NS record";
	}
#endif
	return ns;
}

std::vector<std::string> filter_nameservers( DnsPtr query ) {
	return filter_resource_by_type( query, Type::NS, &ns_filter_function );
}

boost::optional<std::string> filter_first_ns( DnsPtr query ) {
	return maybe_first( filter_nameservers( query ) );
}

boost::optional<std::string> cname_filter_function( DNS::ResourcePtr resource ) {
#ifdef LOGGING
	LOG(INFO) << "Interpreting as cname";
#endif
	boost::optional<std::string> cname;
	boost::shared_ptr<CNameResourceRecord> casted = boost::dynamic_pointer_cast<CNameResourceRecord>(resource);
	if( casted ) {
		cname = casted->get_name().to_string();
	}
#ifdef LOGGING
	else {
		LOG(WARNING) << "Could not interpret record as CName record";
	}
#endif
	return cname;
}

std::vector<std::string> filter_cnames( DnsPtr query ) {
	return filter_resource_by_type( query, Type::CNAME, &cname_filter_function );
}

boost::optional<std::string> filter_first_cname( DnsPtr query ) {
	return maybe_first( filter_cnames( query ) );
}

DnsPtr create_ns_query( DnsPtr other ) {
	DNS::QuestionList qs = other->get_questions();
	if( !qs.empty() ) {
		return DNSBuilder().
			recursion_desired(false).
			is_query().
			question_count(1).
			add_question( Question( qs.at(0)->get_name(), Type::NS, NetClass::IN ) ).
			build_ptr();
	}
#ifdef LOGGING
	LOG(INFO) << "Cannot create question";
#endif
	throw "Cannot create question";
}

DnsPtr create_a_query( DnsPtr other ) {
	DNS::QuestionList qs = other->get_questions();
	if( !qs.empty() ) {
		return DNSBuilder().
			recursion_desired(false).
			is_query().
			question_count(1).
			add_question( Question( qs.at(0)->get_name(), Type::A, NetClass::IN ) ).
			build_ptr();
	}

#ifdef LOGGING
	LOG(INFO) << "Cannot create question";
#endif
	throw "Cannot create question";
}

std::string find_ip_with_name_in_additional( DnsPtr query, const std::string& name ) {
	DNS::ResourceList additionals = query->get_additionals();
	if( !additionals.empty() ) {
		for( DNS::ResourceList::const_iterator i = additionals.begin(); i != additionals.end(); ++i ) {
#ifdef LOGGING
			LOG(INFO) << "Comparign name with: " << (*i)->get_label_name().to_string();
#endif
			if( (*i)->get_type() == Type::A && (*i)->get_label_name() == name ) {
				return ip_from_data( (*i)->get_data() );
			}
		}
	}
#ifdef LOGGING
	LOG(WARNING) << "No additionals found with name: " << name;
#endif
	throw "No additionals found with given name";
}

std::string resolve_nameserver_ip_via_additional( DnsPtr query ) {
	DNS::ResourceList nameservers = query->get_resource_records();
	for( size_t i = 0; i< nameservers.size(); ++i ) {
		DNS::ResourcePtr nameserver = nameservers.at(i);
		if( nameserver->get_type() == Type::NS ) {
			boost::shared_ptr<NsResourceRecord> casted = boost::dynamic_pointer_cast<NsResourceRecord>(nameserver);
			if( casted ) {
				std::string name = casted->get_name().to_string();
				try {
					std::string ip = find_ip_with_name_in_additional( query, name );
					LOG(INFO) << "Returning ip [" << ip << "] for name: " << name;
					return ip;
				} catch(...) {
#ifdef LOGGING
					LOG(WARNING) << "No ip found for: " << name;
#endif
				}
			}
		}
	}

#ifdef LOGGGING
	LOG(WARNING) << "No nameservers found in query";
#endif

	throw "No nameservers found in query";
}

bool is_soa( DnsPtr query, DnsPtr response ) {
	DNS::ResourceList nameservers = response->get_nameservers();
	for( size_t i = 0; i < nameservers.size(); ++i ) {
		DNS::ResourcePtr nameserver = nameservers.at(i);
		if(nameserver->get_type() == Type::SOA ) {
			return true;
		}
	}
	return false;
}

bool is_cname_or_ip_or_end_nameservers( DnsPtr query, DnsPtr response ) {
#ifdef LOGGING
	LOG(INFO) << "Inside ipcnameipnameserver function";
#endif
	DNS::ResourceList answers = response->get_answers();
	for( size_t i = 0; i < answers.size(); ++i ) {
		DNS::ResourcePtr answer = answers.at(i);
#ifdef LOGGING
		LOG(INFO) << "Checking answer for possible match";
#endif
		if( answer->get_type() == Type::A || answer->get_type() == Type::CNAME ) {
			return true;
		}
		if( answer->get_type() == Type::NS ) {
#ifdef LOGGING
			LOG(INFO) << "Checking ns type";
#endif
			boost::shared_ptr<NsResourceRecord> casted = boost::dynamic_pointer_cast<NsResourceRecord>(answer);
			if( casted ) {
				return true;
			}
#ifdef LOGGING
			else {
				LOG(WARNING) << "Could not cast?";
			}
#endif
		}
	}

	return false;
}

DnsPtr recursive_send_and_recieve_internal( const std::string& server, DnsPtr query ) {
	std::cout << "Asking for nameserver from: " << server << std::endl;
	DnsPtr nameserver_response = send_and_receive( server, query );
	if( is_cname_or_ip_or_end_nameservers( query, nameserver_response ) ) {
		return recursive_send_and_recieve( server, query );
	} else {
		return recursive_send_and_recieve_internal( resolve_nameserver_ip_via_additional(nameserver_response), create_ns_query( query ));
	}
}


DnsPtr recursive_send_and_recieve( const std::string& server, DnsPtr query ) {
	std::cout << "First asking the given nameserver" << std::endl;
	DnsPtr first_response = send_and_receive( server, query );
	if( is_cname_or_ip_or_end_nameservers( query, first_response ) ) {
		LOG(INFO) << "Found end point?";
		// TODO also check cname
		MaybeNameOrIp ip_result = filter_first_ip( first_response );
		if( ip_result ) {
			LOG(INFO) << "Found end ip";
			std::cout << *ip_result << std::endl;
			return first_response;
		}

		MaybeNameOrIp cname_result = filter_first_cname( first_response );
		if( cname_result ) {
			LOG(INFO) << "Found end cname";
			std::cout << *cname_result << std::endl;
			return first_response;
		}

		LOG(INFO) << "Is this a nameserver crazy end point at [" << server << "]?";

		return recursive_send_and_recieve( server, create_a_query(query));

	} else if( is_soa( query, first_response )) {
#ifdef LOGGING
			LOG(INFO) << "Sending query to SOA";
#endif
		return recursive_send_and_recieve( server, create_a_query(query));
	} else {
		// lets recurse!
		std::cout << "Starting recursion" << std::endl;
			
		return recursive_send_and_recieve(resolve_nameserver_ip_via_additional(first_response), create_ns_query( query ) );
	}
}

DnsPtr send_and_receive( const std::string& server, DnsPtr query ) {	
	// TODO add timeout
	static Socket socket(SOCK_DGRAM, 16318);
	boost::shared_ptr<Convert> dns_data( new DNSConvert(query) );
	boost::shared_ptr<Consumer> gen(new DataProducer(dns_data));
	boost::function<void(int)> sfunc = boost::bind(&socket_thread_runner, _1, gen);
	socket.connect(server.c_str(), 53, sfunc);

	DnsPtr result;
	//boost::shared_ptr<Consumer> parse( new DNSResponseConsumer(result, query->get_questions().at(0)->get_type() ) );
	boost::shared_ptr<Consumer> parse( new DNSConsumer(result) );
	boost::function<void(int)> rfunc = boost::bind(&socket_thread_runner, _1, parse);
	socket.accept( rfunc );

#ifdef LOGGING
	LOG(INFO) << "Received dns result: " << result->to_string();
#endif

	return result;

}


