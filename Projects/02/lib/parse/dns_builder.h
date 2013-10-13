/*
 * dns_builder.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_builder_h__
#define __dns_builder_h__

#include "dnsmuncher/util/logging.h"

class DNSBuilder {
	public:

		void set_id( unsigned long num) {
			this->id = std::bitset<16>(num);
#ifdef LOGGING
			LOG(INFO) << "Set id to: " << this->id.to_string();
#endif
		}

		DNS build() {
			return DNS(id);
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

