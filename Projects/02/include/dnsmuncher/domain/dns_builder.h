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

class DNSBuilder {
	public:

		DNSBuilder& set_id( unsigned long num) {
			this->id = std::bitset<16>(num);
#ifdef LOGGING
			LOG(INFO) << "Set id to: " << this->id.to_string();
#endif
			return *this;
		}

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

		void recursion_desired( bool rd ) {
			this->rd = rd;
		}

		void authoritative_bit( bool aa ) {
			this->aa = aa;
		}

		void is_response() {
			this->qr = false;
		}
		
		void is_query() {
			this->qr = true;
		}

		void truncated() {
			this->tc = true;
		}

		void recursion_available( bool ra ) {
			this->ra = ra;
		}

		DNS build() {
			return DNS(id, qd_count, an_count, ns_count, ar_count, qr, aa, tc, rd, ra,
					opcode, z, rcode, questions, records);
		}

		boost::shared_ptr<DNS> build_ptr() {
			return boost::shared_ptr<DNS>(new DNS(id, qd_count, an_count, ns_count, ar_count, qr, aa, tc, rd, ra,
					opcode, z, rcode, questions, records));
		}

	protected:
		std::bitset<16> id, qd_count, an_count, ns_count, ar_count;
		bool qr, aa, tc, rd, ra;
		std::bitset<4> opcode;
		std::bitset<3> z;
		std::bitset<4> rcode;
		std::vector<Question> questions;
		std::vector<ResourceRecord> records;
};

#endif /* !__dns_builder_h__ */

