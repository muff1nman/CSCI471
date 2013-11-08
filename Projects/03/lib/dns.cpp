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
#include "dnsmuncher/actors/dns_producer.h"
#include "dnsmuncher/domain/resource_record_all.h"
#include "dnsmuncher/domain/dns_builder.h"
#include "dnsmuncher/socket/socket.h"
#include "dnsmuncher/parse/ip.h"
#ifdef CACHING
#include "dnsmuncher/cache.h"
#endif
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
				if( resources.at(i)->get_type() == t ) { //|| t == Type::ANY ) {
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

std::string resolve_nameserver_ip_via_additional( DnsPtr query, Socket& socket ) {
	DNS::ResourceList nameservers = query->get_resource_records();
	for( size_t i = 0; i< nameservers.size(); ++i ) {
		DNS::ResourcePtr nameserver = nameservers.at(i);
		if( nameserver->get_type() == Type::NS ) {
			boost::shared_ptr<NsResourceRecord> casted = boost::dynamic_pointer_cast<NsResourceRecord>(nameserver);
			if( casted ) {
				std::string name = casted->get_name().to_string();
				try {
					std::string ip = find_ip_with_name_in_additional( query, name );
#ifdef LOGGING
					LOG(INFO) << "Returning ip [" << ip << "] for name: " << name;
#endif
					return ip;
				} catch(...) {
#ifdef LOGGING
					LOG(WARNING) << "No ip found for: " << name;
#endif
					DnsPtr name_query = DNSBuilder().
						recursion_desired(false).
						is_query().
						question_count(1).
						add_question( Question( name, Type::A, NetClass::IN ) ).
						build_ptr();

					// try to resolve nameserver
					DnsMaybePtr name_result = recursive_send_and_recieve( ROOT_SERVER, name_query, socket );
					if( name_result ) { 
						MaybeNameOrIp name_ip = filter_first_ip( *name_result );
						if( name_ip ) {
							return *name_ip;
						}
					}
				}
			}
		}
	}


#ifdef LOGGGING
	LOG(WARNING) << "No nameservers found in query";
#endif

	throw "No nameservers found in query";
}

bool nxdomain( DnsPtr query, DnsPtr response ) {
	return response->response_code() != DNS::NO_ERROR;
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

bool is_ip( DnsPtr response ) {
	DNS::ResourceList answers = response->get_answers();
	for( size_t i = 0; i < answers.size(); ++i ) {
		DNS::ResourcePtr answer = answers.at(i);
		if( answer->get_type() == Type::A ) {
			return true;
		}
	}
	return false;
}

// TODO code dup
bool is_cname( DnsPtr response ) {
	DNS::ResourceList answers = response->get_answers();
	for( size_t i = 0; i < answers.size(); ++i ) {
		DNS::ResourcePtr answer = answers.at(i);
		if( answer->get_type() == Type::CNAME ) {
			return true;
		}
	}
	return false;
}

bool is_end_nameservers( DnsPtr response ) {
	DNS::ResourceList answers = response->get_answers();
	for( size_t i = 0; i < answers.size(); ++i ) {
		DNS::ResourcePtr answer = answers.at(i);
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

bool is_cname_or_ip_or_end_nameservers( DnsPtr response ) {
	return is_end_nameservers(response) || is_cname( response ) || is_ip( response );
}

DnsMaybePtr recursive_send_and_recieve( const std::string& server, DnsPtr query, Socket& socket, bool print_intermediate ) {
	DnsMaybePtr first_response = send_and_receive( server, query, socket, print_intermediate );
	if( !first_response ) { 
		if(print_intermediate ) {
			std::cout << "No valid response" << std::endl << std::endl;
		}
		return first_response;
	}
	if(print_intermediate) { 
		std::cout << (*first_response)->debug_response() << std::endl;
	}
	if( nxdomain(query, *first_response) ) {
#ifdef LOGGING
		LOG(INFO) << "No such domain response";
#endif
		if( print_intermediate) {
			std::cout << "No domain found \\/" << std::endl << std::endl;
		}
		return first_response;
	} else if( is_cname_or_ip_or_end_nameservers( *first_response ) ) {

		MaybeNameOrIp ip_result = filter_first_ip( *first_response );
		if( ip_result ) {
			if(print_intermediate) {
				std::cout  << "Interpreting previous as A record" << std::endl << std::endl;
			}
			return first_response;
		}

		MaybeNameOrIp cname_result = filter_first_cname( *first_response );
		if( cname_result ) {
			if(print_intermediate) {
				std::cout  << "Interpreting previous as CNAME record" << std::endl;
				std::cout << "Initializing new recursive query for Canonical Name [" << *cname_result<< "]" << std::endl << std::endl;
			}
			DnsPtr cname_query = DNSBuilder().
				recursion_desired(false).
				is_query().
				question_count(1).
				add_question( Question( *cname_result, Type::NS, NetClass::IN ) ).
				build_ptr();

			return recursive_send_and_recieve( ROOT_SERVER, cname_query, socket, print_intermediate );
		}

		if(print_intermediate) {
			std::cout << "Interpreting previous as end to NS chain. Changing question type to A" << std::endl << std::endl;
		}
		return recursive_send_and_recieve( server, create_a_query(query), socket, print_intermediate );

	} else if( is_soa( query, *first_response )) {
			if(print_intermediate) {
				std::cout  << "Interpreting previous as SOA record" << std::endl << std::endl;
			}
#ifdef LOGGING
			LOG(INFO) << "Sending query to SOA";
#endif
		return recursive_send_and_recieve( server, create_a_query(query), socket, print_intermediate);
	} else {
			if(print_intermediate) {
				std::cout  << "Answer should contain NS." << std::endl << std::endl;
			}
		return recursive_send_and_recieve(resolve_nameserver_ip_via_additional(*first_response, socket), create_ns_query( query ), socket, print_intermediate );
	}
}

DnsMaybePtr check_or_add_to_cache( DnsPtr query, DnsMaybePtr result ) {
	static DnsCache cache;
	DnsMaybePtr cached;
	if( result ) {
		add_to_cache( cache, query, *result );
	} else {
		cached = get_from_cache( cache, query );
	}
	return cached;
}

DnsMaybePtr query_once_and_then_try_recursive( const std::string& server, DnsPtr query, Socket& socket, bool print_intermediate) {
	DnsMaybePtr first_response;
#ifdef CACHING
	DnsMaybePtr from_cache = check_or_add_to_cache( query, first_response );
	if( from_cache ) {
		return from_cache;
	}
#endif
	if( print_intermediate ) {
		std::cout << "Trying given server [" << server << "]" << std::endl;
	}
	first_response = send_and_receive( server, query, socket );
	if( first_response ) {
		if( print_intermediate ) {
			//std::cout << (*first_response)->debug_response() << std::endl;
		}
		if( is_ip( *first_response ) ) {
			MaybeNameOrIp ip_result = filter_first_ip( *first_response );
			if( ip_result ) {
#ifdef CACHING
				check_or_add_to_cache( query, first_response);
#endif
				return first_response;
			}
		}
	}

	if( print_intermediate ) {
		std::cout << "No valid response, attempt recursive lookup" << std::endl;
	}


	first_response = recursive_send_and_recieve( ROOT_SERVER, query, socket, print_intermediate );
#ifdef CACHING
	check_or_add_to_cache( query, first_response);
#endif
	return first_response;
}

void server(int socket) {
	boost::shared_ptr<Consumer> handler( new DnsProducer() );	
	handler->run( socket );
}

DnsMaybePtr send_and_receive( const std::string& server, DnsPtr query, Socket& socket, bool print_intermediate ) {	
	DnsMaybePtr result;
	boost::shared_ptr<Convert> dns_data( new DNSConvert(query) );
	boost::shared_ptr<Consumer> gen(new DataProducer(dns_data));
	boost::function<void(int)> sfunc = boost::bind(&socket_thread_runner, _1, gen);
	socket.connect(server.c_str(), DNS_PORT, sfunc);

	//boost::shared_ptr<Consumer> parse( new DNSResponseConsumer(result, query->get_questions().at(0)->get_type() ) );
	boost::shared_ptr<Consumer> parse( new DNSConsumer(result) );
	boost::function<void(int)> rfunc = boost::bind(&socket_thread_runner, _1, parse);
	socket.accept( rfunc );

	return result;

}


