/*
 * dns_producer.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dnsmuncher/actors/dns_producer.h"
#include "dnsmuncher/dns.h"
#include "dnsmuncher/domain/dns_builder.h"
#include "dnsmuncher/parse/dns.h"
#include "dnsmuncher/socket/helper.h"
#include "dnsmuncher/data/convert_all.h"
#include "dnsmuncher/actors/data_producer.h"

void DnsProducer::run(int socket_fd) {
	sockaddr_in remote_info;
	socklen_t remote_info_size;
#ifdef LOGGING
	LOG(INFO) << "Starting new read";
#endif
	BytesContainer raw_data = all_data(socket_fd, 1200, remote_info, remote_info_size );
	DnsMaybePtr parsed_query = from_data_as_ptr( raw_data );
	if( parsed_query ) {
#ifdef LOGGING
		LOG(INFO) << "receieved: " << (*parsed_query)->to_string();
#endif
		Socket socket(SOCK_DGRAM, DNSMUNCHER_SEND_PORT);
		socket.set_timeout( TIMEOUT_IN_USEC, TIMEOUT_IN_SEC );
#ifdef LOGGING
		LOG(INFO) << "Created auxilary socket";
#endif
		DnsMaybePtr lookup = query_once_and_then_try_recursive( ROOT_SERVER, *parsed_query, socket );
		close(socket.get_socket());
		DnsPtr to_send_back;
		if( lookup && (*lookup)->get_answers().size() > 0) {
			DNSBuilder b;
			b.is_response().
				set_id( (*parsed_query)->get_id());
			DNS::QuestionList question_list = (*parsed_query)->get_questions();
			for( size_t i = 0; i < question_list.size(); ++i ) {
				b.add_question( (question_list.at(i)) );
			}
			b.question_count( question_list.size() );

			DNS::ResourceList answer_list = (*lookup)->get_answers();
			size_t count = 0;
			for( size_t i = 0; i < answer_list.size(); ++i ) {
#ifdef LOGGING
				LOG(INFO) << "Adding resource record: " << (answer_list.at(i)->to_string());
#endif
				DNS::ResourcePtr answer = answer_list.at(i);
				if( answer->get_type() == Type::A ) {
					b.add_resource( answer );
					++count;
				}
			}
			b.answer_count( count );

			b.recursion_available(true);
			b.authoritative_bit( (*lookup)->is_authoritative() );

			to_send_back = b.build_ptr();
				
		} else {
			to_send_back = DNSBuilder().
				is_response().
				set_id( (*parsed_query)->get_id()).
				return_code( std::bitset<DNS::RCODE_FIELD_LENGTH>(DNS::SERVER_FAILURE) ).
				build_ptr();

		}
#ifdef LOGGING
		LOG(INFO) << "connectin";
#endif
		int connection_result = connect( socket_fd, (sockaddr*) &remote_info, remote_info_size );
		if(connection_result < 0 ) { 
#ifdef LOGGING
			LOG(WARNING) << "Could not connect: " << strerror(errno);
#endif
		} else {
#ifdef LOGGING
		LOG(INFO) << "connected";
#endif
			boost::shared_ptr<Convert> dns_data( new DNSConvert(to_send_back) );
			boost::shared_ptr<Consumer> gen(new DataProducer(dns_data));
			gen->run(socket_fd);
		}

#ifdef LOGGING
		LOG(INFO) << "Done with socket";
#endif

	}
}




