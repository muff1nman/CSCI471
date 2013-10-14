/*
 * dns_builder.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_builder_h__
#define __dns_builder_h__

#include "dnsmuncher/util/logging.h"
#include <boost/shared_ptr.hpp>
#include "dns.h"

class DNSBuilder {
	public:

		DNSBuilder() {
			this->zero_all();
		}

		DNSBuilder& set_id( unsigned long num) {
			this->id = std::bitset<16>(num);
#ifdef LOGGING
			LOG(INFO) << "Set id to: " << this->id.to_string();
#endif
			do_common();
		}

		DNSBuilder& add_question( const Question q ) {
			questions.push_back( q );
			this->qd_count = std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH>(questions.size());
			do_common();
		}

		DNSBuilder& add_additional( const ResourceRecord r ) {
			additional_records.push_back( r );
			this->ar_count = std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH>(additional_records.size());
			do_common();
		}

		DNSBuilder& add_answer( const ResourceRecord r ) {
			answers.push_back( r );
			this->an_count = std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH>(answers.size());
			do_common();
		}

		DNSBuilder& add_nameserver( const ResourceRecord r ) {
			nameserver_records.push_back( r );
			this->ns_count = std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH>(nameserver_records.size());
			do_common();
		}

		DNSBuilder& recursion_desired( bool rd ) {
			this->rd = rd;
			do_common();
		}

		DNSBuilder& authoritative_bit( bool aa ) {
			this->aa = aa;
			do_common();
		}

		DNSBuilder& is_response() {
			this->qr = false;
			do_common();
		}

		DNSBuilder& is_response( bool response ) {
			this->qr = !response;
			do_common();
		}
		
		DNSBuilder& is_query( bool query ) {
			this->qr = query;
			do_common();
		}

		DNSBuilder& is_query() {
			this->qr = true;
			do_common();
		}

		DNSBuilder& truncated( bool tc ) {
			this->tc = tc;
			do_common();
		}

		DNSBuilder& recursion_available( bool ra ) {
			this->ra = ra;
			do_common();
		}

		DNSBuilder& op_code( unsigned int num ) {
			this->op_code(std::bitset<DNS::OPCODE_FIELD_LENGTH>(num));
			do_common();
		}

		DNSBuilder& op_code( std::bitset<DNS::OPCODE_FIELD_LENGTH> bits ) {
			this->opcode = bits;
			do_common();
		}

		DNSBuilder& zeros( std::bitset<DNS::Z_FIELD_LENGTH> bits ) {
			this->z = bits;
			do_common();
		}

		DNSBuilder& return_code( std::bitset<DNS::RCODE_FIELD_LENGTH> bits ) {
			this->rcode = bits;
			do_common();
		}

		DNS build() {
			return DNS(id, qd_count, an_count, ns_count, ar_count, qr, aa, tc, rd, ra,
					opcode, z, rcode, questions, combine_everything_but_questions());
		}

		boost::shared_ptr<DNS> build_ptr() {
			return boost::shared_ptr<DNS>(new DNS(id, qd_count, an_count, ns_count, ar_count, qr, aa, tc, rd, ra,
					opcode, z, rcode, questions, combine_everything_but_questions()));
		}

	protected:
		std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH> id, qd_count, an_count, ns_count, ar_count;
		bool qr, aa, tc, rd, ra;
		std::bitset<DNS::OPCODE_FIELD_LENGTH> opcode;
		std::bitset<DNS::Z_FIELD_LENGTH> z;
		std::bitset<DNS::RCODE_FIELD_LENGTH> rcode;
		std::vector<Question> questions;
		std::vector<ResourceRecord> additional_records;
		std::vector<ResourceRecord> answers;
		std::vector<ResourceRecord> nameserver_records;

	private:
		DNSBuilder& do_common() {
			return *this;
		}

		std::vector<ResourceRecord> combine_everything_but_questions() {
			std::vector<ResourceRecord> rrs(additional_records.size() + answers.size() + nameserver_records.size());
			rrs.insert( rrs.end(), additional_records.begin(), additional_records.end() );
			rrs.insert( rrs.end(), answers.begin(), answers.end() );
			rrs.insert( rrs.end(), nameserver_records.begin(), nameserver_records.end() );
			return rrs;
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
			additional_records.clear();
			answers.clear();
			nameserver_records.clear();
			qr = false;
			aa = false;
			tc = false;
			rd = false;
			ra = false;
		}
};

#endif /* !__dns_builder_h__ */

