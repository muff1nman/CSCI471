/*
 * dns_producer.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dns/config.h"
#include "dns/actors/dns_producer.h"
#include "dns/dns.h"
#include "dns/domain/dns_builder.h"
#include "dns/parse/dns.h"
#include "dns/data/convert_all.h"

#include "networkmuncher/actors/data_producer.h"

void DnsProducer::run(Socket* socket) {
	sockaddr_in remote_info;
	socklen_t remote_info_size;

	////////////////////////////////////////////////
	// Read dns question
	////////////////////////////////////////////////
	
#ifdef LOGGING
	LOG(INFO) << "Starting new read";
#endif
	BytesContainer raw_data = socket->recv_from( remote_info, remote_info_size, 1200 );
	DnsMaybePtr parsed_query = from_data_as_ptr( raw_data );
	if( parsed_query ) {
#ifdef LOGGING
		LOG(INFO) << "receieved: " << (*parsed_query)->to_string();
#endif

		////////////////////////////////////////////////
		// Retrieve dns result for answer to question.  Use block to enforce only
		// using aux_socket for this single purpose and so that destructor gets
		// called
		////////////////////////////////////////////////

		DnsMaybePtr lookup;
		{
			Socket aux_socket(SOCK_DGRAM, DNSMUNCHER_SEND_PORT);
			aux_socket.set_timeout( TIMEOUT_IN_USEC, TIMEOUT_IN_SEC );
#ifdef LOGGING
			LOG(INFO) << "Created auxilary socket";
#endif
#ifdef DAEMON_DEBUG
			lookup = query_once_and_then_try_recursive( ROOT_SERVER, *parsed_query, aux_socket, true );
#else
			lookup = query_once_and_then_try_recursive( ROOT_SERVER, *parsed_query, aux_socket );
#endif
		}

		////////////////////////////////////////////////
		// Formulate answer to send back
		////////////////////////////////////////////////

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

		////////////////////////////////////////////////
		// Send back the answer
		////////////////////////////////////////////////
		boost::shared_ptr<Convert> dns_data( new DNSConvert(to_send_back) );
		boost::shared_ptr<Consumer> gen(new DataProducer(dns_data));

		socket->connect((sockaddr*) &remote_info, remote_info_size, gen);

#ifdef LOGGING
		LOG(INFO) << "Done with socket";
#endif

	}
}




