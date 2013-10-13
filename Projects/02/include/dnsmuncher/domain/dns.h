/*
 * dns.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_h__
#define __dns_h__

#include "dnsmuncher/util/logging.h"
#include "dnsmuncher/util/byte.h"

#include <bitset>
#include <vector>
#include <string>
#include <cstdlib>
#include "resource_record.h"
#include "question.h"

class DNS : public Logging {
	// TODO
	public:
		DNS() {
			this->generate_id();
			this->set_is_query();
		}

		virtual std::string stringify_object() const {
			return "DNS OBJECT";
		}

		friend class DNSConvert;

	public:
		void add_question( const Question q ) {
			// make sure to increment length
			// TODO
		}

		void add_additional( const ResourceRecord r ) {
			// TODO
		}

		void add_answer( const ResourceRecord r ) {
			// TODO	
		}

		void add_nameserver( const ResourceRecord r ) {
			// TODO
		}

		void set_recursion_desired( bool rd ) {
			this->rd = rd;
		}

		void set_authoritative_bit( bool aa ) {
			this->aa = aa;
		}

		void set_is_response() {
			this->qr = false;
		}
		
		void set_is_query() {
			this->qr = true;
		}

		void set_truncated() {
			this->tc = true;
		}

		void set_recursion_available( bool ra ) {
			this->ra = ra;
		}


	private:
		// TODO maybe hide the implementation of bitset?
		std::bitset<16> id, qd_count, an_count, ns_count, ar_count;
		bool qr, aa, tc, rd, ra;
		std::bitset<4> opcode;
		std::bitset<3> z;
		std::bitset<4> rcode;
		std::vector<Question> questions;
		std::vector<ResourceRecord> records;

		void set_z_as_zeros() {
			// TODO 
		}

		void set_rcode_for_question() {
			// TODO
		}

		void set_opcode_as_standard_query() {
			// TODO
		}

		void generate_id() {
			id = std::bitset<16>(rand());
		}
		
};

#endif /* !__dns_h__ */

