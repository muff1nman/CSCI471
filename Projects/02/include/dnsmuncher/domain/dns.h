/*
 * dns.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_h__
#define __dns_h__

#include "dnsmuncher/util/logging.h"
#include "dnsmuncher/util/byte/byte.h"

#include <bitset>
#include <vector>
#include <string>
#include <cstdlib>
#include "resource_record.h"
#include "question.h"

#include <ostream>

class DNS : public Logging {
	public:

		static const size_t GENERIC_HEADER_FIELD_LENGTH = 16;
		static const size_t OPCODE_FIELD_LENGTH = 4;
		static const size_t Z_FIELD_LENGTH = 3;
		static const size_t RCODE_FIELD_LENGTH = 4;

		virtual std::string stringify_object() const {
			std::string info("");
			info += std::string("id: ") + this->id.to_string() + list_sep;
			return info;
		}

		friend class DNSConvert;


		/**
		 * For testing purposes
		 */
		bool header_equal( const DNS& other ) const {
			return this->id == other.id &&
				this->qd_count == other.qd_count &&
				this->an_count == other.an_count &&
				this->ns_count == other.ns_count &&
				this->ar_count == other.ar_count &&
				this->qr == other.qr &&
				this->aa == other.aa &&
				this->tc == other.tc &&
				this->rd == other.rd &&
				this->ra == other.ra && 
				this->opcode == other.opcode &&
				this->z == other.z &&
				this->rcode == other.rcode;
		}

		/**
		 * For testing purposes
		 */
		bool operator==( const DNS& other ) const {
			return header_equal(other);
			// TODO recuse into Question and Resource
		}

		/**
		 * For testing purposes
		 */
		friend std::ostream& operator<<(std::ostream& os, const DNS& dns) {
			os << std::endl;
			os<< "id: " << dns.id << std::endl;
			os<< "qt_count: " << dns.qd_count << std::endl;
			os<< "an_count : " << dns.an_count << std::endl;
			os<< "ns_count : " << dns.ns_count << std::endl;
			os<< "ar_count : " << dns.ar_count << std::endl;
			os<< "qr : " << dns.qr << std::endl;
			os<< "aa : " << dns.aa << std::endl;
			os<< "tc : " << dns.tc << std::endl;
			os<< "rd : " << dns.rd << std::endl;
			os<< "ra : " << dns.ra << std::endl;
			os<< "opcode : " << dns.opcode << std::endl;
			os<< "z : " << dns.z << std::endl;
			os<< "rcode : " << dns.rcode << std::endl;
			return os;
		}

		DNS( 
				std::bitset<GENERIC_HEADER_FIELD_LENGTH> id, 
				std::bitset<GENERIC_HEADER_FIELD_LENGTH> qd_count,
				std::bitset<GENERIC_HEADER_FIELD_LENGTH> an_count,
				std::bitset<GENERIC_HEADER_FIELD_LENGTH> ns_count,
				std::bitset<GENERIC_HEADER_FIELD_LENGTH> ar_count,
				bool qr,
				bool aa,
				bool tc,
				bool rd,
				bool ra,
				std::bitset<OPCODE_FIELD_LENGTH> opcode,
				std::bitset<Z_FIELD_LENGTH> z,
				std::bitset<RCODE_FIELD_LENGTH> rcode,
				std::vector<Question> questions,
				std::vector<ResourceRecord> records
			 ) : 
			id(id),
			qd_count(qd_count),
			an_count(an_count),
			ns_count(ns_count),
			ar_count(ar_count),
			qr(qr),
			aa(aa),
			tc(tc),
			rd(rd),
			ra(ra),
			opcode(opcode),
			z(z),
			rcode(rcode),
			questions(questions),
			records(records)
			{ }

	private:
		// dont use
		DNS() { };
		// TODO maybe hide the implementation of bitset?
		std::bitset<GENERIC_HEADER_FIELD_LENGTH> id, qd_count, an_count, ns_count, ar_count;
		bool qr, aa, tc, rd, ra;
		std::bitset<OPCODE_FIELD_LENGTH> opcode;
		std::bitset<Z_FIELD_LENGTH> z;
		std::bitset<RCODE_FIELD_LENGTH> rcode;
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
			id = std::bitset<GENERIC_HEADER_FIELD_LENGTH>(rand());
		}
		
};

#endif /* !__dns_h__ */

