/*
 * dns_builder.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_builder_h__
#define __dns_builder_h__

#include "networkmuncher/util/logging.h"
#include "networkmuncher/util/byte/byte.h"
#include <boost/shared_ptr.hpp>
#include "dns.h"
#include <stdlib.h>
#include <time.h>

class DNSBuilder : public Logging {

	public:

		DNSBuilder() {
			this->zero_all();
			srand(time(NULL));
			this->random_id();
		}

		DNSBuilder& random_id() {
			this->id = rand() % 65535;
			return do_common();
		}

		DNSBuilder& set_id( generic_number num) {
			this->id = std::bitset<16>(num);
			return do_common();
		}

		DNSBuilder& add_question( const DNS::QuestionPtr& q ) {
			questions.push_back( q );
			return do_common();
		}

		DNSBuilder& add_question( const Question& q ) {
			return add_question( DNS::QuestionPtr( new Question(q) ));
		}

		DNSBuilder& add_resource( const DNS::ResourcePtr& r ) {
			other_records.push_back( r );
			return do_common();
		}

		DNSBuilder& add_resource( const ResourceRecord& r ) {
			return add_resource( DNS::ResourcePtr( new ResourceRecord(r) ) );
		}

		DNSBuilder& recursion_desired( bool rd ) {
			this->rd = rd;
			return do_common();
		}

		DNSBuilder& authoritative_bit( bool aa ) {
			this->aa = aa;
			return do_common();
		}

		// TODO refactor internal query bit into response bit
		DNSBuilder& is_response() {
			this->response = true;
			return do_common();
		}

		DNSBuilder& is_response( bool response ) {
			this->response = response;
			return do_common();
		}
		
		DNSBuilder& is_query( bool query ) {
			this->response = !query;
			return do_common();
		}

		DNSBuilder& is_query() {
			this->response = false;
			return do_common();
		}

		DNSBuilder& truncated( bool tc ) {
			this->tc = tc;
			return do_common();
		}

		DNSBuilder& recursion_available() {
			return recursion_available( true );
		}

		DNSBuilder& recursion_available( bool ra ) {
			this->ra = ra;
			return do_common();
		}

		DNSBuilder& op_code( opcode_number num ) {
			this->op_code(std::bitset<DNS::OPCODE_FIELD_LENGTH>(num));
			return do_common();
		}

		DNSBuilder& op_code( std::bitset<DNS::OPCODE_FIELD_LENGTH> bits ) {
			this->opcode = bits;
			return do_common();
		}

		DNSBuilder& zeros( std::bitset<DNS::Z_FIELD_LENGTH> bits ) {
			this->z = bits;
			return do_common();
		}

		DNSBuilder& return_code( std::bitset<DNS::RCODE_FIELD_LENGTH> bits ) {
			this->rcode = bits;
			return do_common();
		}

		DNSBuilder& question_count( std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH> qd_count ) {
			this->qd_count = qd_count;
			return do_common();
		}

		DNSBuilder& question_count( generic_number num ) {
			return question_count( std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH>(num) );
		}

		DNSBuilder& nameserver_count( std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH> ns_count ) {
			this->ns_count = ns_count;
			return do_common();
		}

		DNSBuilder& nameserver_count( generic_number num ) {
			return nameserver_count( std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH>(num) );
		}

		DNSBuilder& answer_count( std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH> an_count ) { 
			this->an_count = an_count;
			return do_common();
		}

		DNSBuilder& answer_count( generic_number num ) {
			return answer_count( std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH>(num) );
		}

		DNSBuilder& additional_count( std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH> ad_count ) {
			this->ar_count = ad_count;
			return do_common();
		}

		DNSBuilder& additional_count( generic_number num ) {
			return additional_count( std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH>(num) );
		}

		DNS build() const {
			return DNS(id, qd_count, an_count, ns_count, ar_count, response, aa, tc, rd, ra,
					opcode, z, rcode, questions, other_records);
		}

		boost::shared_ptr<DNS> build_ptr() const {
			return boost::shared_ptr<DNS>(new DNS(id, qd_count, an_count, ns_count, ar_count, response, aa, tc, rd, ra,
					opcode, z, rcode, questions, other_records));
		}

		std::string stringify_object() const {
			DNS temp = this->build();
			return temp.stringify_object();
		}

		/**
		 * For testing purposes
		 */
		friend std::ostream& operator<<(std::ostream& os, const DNSBuilder& dns) {
			os << std::endl;
			os<< dns.to_string();
			return os;
		}

	protected:
		std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH> id, qd_count, an_count, ns_count, ar_count;
		bool response, aa, tc, rd, ra;
		std::bitset<DNS::OPCODE_FIELD_LENGTH> opcode;
		std::bitset<DNS::Z_FIELD_LENGTH> z;
		std::bitset<DNS::RCODE_FIELD_LENGTH> rcode;
		DNS::QuestionList questions;
		DNS::ResourceList other_records;

	private:
		DNSBuilder& do_common() {
			return *this;
		}

		DNSBuilder& zero_all() {
			id.reset();
			qd_count.reset();
			an_count.reset();
			ns_count.reset();
			ar_count.reset();
			opcode.reset();
			z.reset();
			z.reset();
			rcode.reset();
			questions.clear();
			other_records.clear();
			response = false;
			aa = false;
			tc = false;
			rd = false;
			ra = false;
			return do_common();
		}
};

#endif /* !__dns_builder_h__ */

