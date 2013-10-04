/*
 * dns.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_h__
#define __dns_h__

#include <bitset>
#include <vector>
#include "resource_record.h"
#include "question.h"
#include "dnsmuncher/util/byte.h"

class DNS {
	// TODO
	//public:
		//DNS( );
	private:
		// TODO maybe hide the implementation of bitset?
		std::bitset<16> id, qd_count, an_count, ns_count, ar_count;
		bool qr, aa, tc, rd, ra;
		std::bitset<4> opcode;
		std::bitset<3> z;
		std::bitset<4> rcode;
		std::vector<Question> questions;
		std::vector<ResourceRecord> records;
		
};

#endif /* !__dns_h__ */

