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
#include "dnsmuncher/socket/socket.h"
#include "dnsmuncher/parse/ip.h"
#include "dnsmuncher/util/collection.h"
#include <boost/bind.hpp>
#include <string>

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

std::vector<std::string> filter_resource_by_type( boost::shared_ptr<DNS> query, Type t, FilterFunction f ) {
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

std::vector<std::string> filter_ips( boost::shared_ptr<DNS> query ) {
	return filter_resource_by_type( query, Type::A, &ip_filter_function );
}

boost::optional<std::string> filter_first_ip( boost::shared_ptr<DNS> query ) {
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

std::vector<std::string> filter_nameservers( boost::shared_ptr<DNS> query ) {
	return filter_resource_by_type( query, Type::NS, &ns_filter_function );
}

boost::optional<std::string> filter_first_ns( boost::shared_ptr<DNS> query ) {
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

std::vector<std::string> filter_cnames( boost::shared_ptr<DNS> query ) {
	return filter_resource_by_type( query, Type::CNAME, &cname_filter_function );
}

boost::optional<std::string> filter_first_cname( boost::shared_ptr<DNS> query ) {
	return maybe_first( filter_cnames( query ) );
}

void send_and_receive( const std::string& server, boost::shared_ptr<DNS> query ) {	
	Socket socket(SOCK_DGRAM, 16318);
	boost::shared_ptr<Convert> dns_data( new DNSConvert(query) );
	boost::shared_ptr<Consumer> gen(new DataProducer(dns_data));
	boost::function<void(int)> sfunc = boost::bind(&socket_thread_runner, _1, gen);
	socket.connect(server.c_str(), 53, sfunc);

	boost::shared_ptr<DNS> result;
	boost::shared_ptr<Consumer> parse( new DNSResponseConsumer(result, query->get_questions().at(0)->get_type() ) );
	boost::function<void(int)> rfunc = boost::bind(&socket_thread_runner, _1, parse);
	socket.accept( rfunc );

#ifdef LOGGING
	LOG(INFO) << "Received dns result: " << result->to_string();
#endif

}


