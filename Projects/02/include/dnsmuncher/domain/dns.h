/*
 * dns.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __domain_dns_h__
#define __domain_dns_h__

#include "dnsmuncher/util/logging.h"
#include "dnsmuncher/util/byte/byte.h"
#include "resource_record.h"
#include "question.h"

#include <bitset>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <ostream>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <boost/iterator/indirect_iterator.hpp>

/**
 * A DNS class to represent any DNS packet.
 */
class DNS : public Logging {
	public:

		typedef boost::shared_ptr<Question> QuestionPtr;
		typedef boost::shared_ptr<ResourceRecord> ResourcePtr;

		typedef std::vector< QuestionPtr > QuestionList;
		typedef std::vector< ResourcePtr > ResourceList;

		static const size_t GENERIC_HEADER_FIELD_LENGTH = 16; 
		static const size_t OPCODE_FIELD_LENGTH = 4; 
		static const size_t Z_FIELD_LENGTH = 3; 
		static const size_t RCODE_FIELD_LENGTH = 4; 
		static const size_t POINTER_LENGTH = 16; 

		static const size_t QR_OFFSET = 15;
		static const size_t OPCODE_OFFSET = 11;
		static const size_t AA_OFFSET = 10;
		static const size_t TC_OFFSET = 9;
		static const size_t RD_OFFSET = 8;
		static const size_t RA_OFFSET = 7;
		static const size_t Z_OFFSET = 4;
		static const size_t RCODE_OFFSET = 0;

		static const size_t MAX_LABEL_SIZE = 63;

		// return codes
		static const size_t NO_ERROR = 0;
		static const size_t FORMAT_ERROR = 1;
		static const size_t SERVER_FAILURE = 2;
		static const size_t NAME_ERROR = 3;
		static const size_t NOT_IMPLEMENTED = 4;
		static const size_t REFUSED = 5;

		std::string stringify_object() const {
			std::stringstream info;
			info << std::string("id: ") << this->id.to_string() << list_sep;
			info << std::string("qd_count: ") << this->qd_count.to_string() << list_sep;
			info << std::string( "an_count : ") << this->an_count.to_string() << list_sep;
			info << std::string( "ns_count : ") << this->ns_count.to_string() << list_sep;
			info << std::string( "ar_count : ") << this->ar_count.to_string() << list_sep;
			info << std::string( "response : ") << this->response << list_sep;
			info << std::string( "aa : ") << this->aa << list_sep;
			info << std::string( "tc : ") << this->tc << list_sep;
			info << std::string( "rd : ") << this->rd << list_sep;
			info << std::string( "ra : ") << this->ra << list_sep;
			info << std::string( "opcode : ") << this->opcode.to_string() << list_sep;
			info << std::string( "z : ") << this->z.to_string() << list_sep;
			info << std::string( "rcode : ") << this->rcode.to_string() << list_sep;
			info << std::string("questions: ") + nested_start;
			for( size_t i = 0; i < questions.size(); ++i ) {
				info << questions.at(i)->to_string() + list_sep;
			}
			info << nested_finish;
			info << list_sep;
			info <<  std::string("records: ") + nested_start;
			for( size_t i = 0; i < records.size(); ++i ) {
				info << records.at(i)->to_string() + list_sep;
			}
			info << nested_finish;
			return info.str();
		}

		/**
		 * Why? Becuase I thought to_string was a bit ugly but I needed to keep
		 * to_string around for its sweet compactness
		 */
		std::string debug_response() const {
			std::stringstream info;
			info << "DNS response:\n";
			info << "  Authoritative?: " << this->aa << "\n";
			info << "  Response Code: " << this->rcode.to_string() << "\n";
			for( size_t i = 0; i < records.size(); ++i ) {
				if( i == 0 ) {
					info << "  Records:\n";
				}
				info << records.at(i)->debug_string(4) << "\n";
			}

			return info.str();
		}

		friend class DNSConvert;

		/**
		 * For testing purposes
		 */
		bool header_equal( const DNS& other ) const {
			bool ret_val = this->id == other.id &&
				this->qd_count == other.qd_count &&
				this->an_count == other.an_count &&
				this->ns_count == other.ns_count &&
				this->ar_count == other.ar_count &&
				this->response == other.response &&
				this->aa == other.aa &&
				this->tc == other.tc &&
				this->rd == other.rd &&
				this->ra == other.ra && 
				this->opcode == other.opcode &&
				this->z == other.z &&
				this->rcode == other.rcode;
			return ret_val;

		}

		/** 
		 * For testing purposes
		 */
		bool content_equal( const DNS& other ) const {
#ifdef LOGGING
			LOG(INFO) << "Checking contents are equal";
#endif
			bool value =
				this->questions.size() == other.questions.size() &&
				this->records.size() == other.records.size() &&
				std::equal(boost::make_indirect_iterator(this->questions.begin()),
						boost::make_indirect_iterator(this->questions.end()),
						boost::make_indirect_iterator(other.questions.begin())) &&
				std::equal(boost::make_indirect_iterator(this->records.begin()),
						boost::make_indirect_iterator(this->records.end()),
						boost::make_indirect_iterator(other.records.begin()));

			return value;
		}

		/**
		 * For testing purposes
		 */
		bool operator==( const DNS& other ) const {
			return header_equal(other) && content_equal(other);
		}

		/**
		 * For testing purposes
		 */
		friend std::ostream& operator<<(std::ostream& os, const DNS& dns) {
			os << std::endl;
			os<< dns.to_string();
			return os;
		}

		DNS( 
				std::bitset<GENERIC_HEADER_FIELD_LENGTH> id, 
				std::bitset<GENERIC_HEADER_FIELD_LENGTH> qd_count,
				std::bitset<GENERIC_HEADER_FIELD_LENGTH> an_count,
				std::bitset<GENERIC_HEADER_FIELD_LENGTH> ns_count,
				std::bitset<GENERIC_HEADER_FIELD_LENGTH> ar_count,
				bool response,
				bool aa,
				bool tc,
				bool rd,
				bool ra,
				std::bitset<OPCODE_FIELD_LENGTH> opcode,
				std::bitset<Z_FIELD_LENGTH> z,
				std::bitset<RCODE_FIELD_LENGTH> rcode,
				QuestionList questions,
				ResourceList records
			 ) : 
			id(id),
			qd_count(qd_count),
			an_count(an_count),
			ns_count(ns_count),
			ar_count(ar_count),
			response(response),
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

		const QuestionList get_questions() const {
			return this->questions;
		}

		const ResourceList get_answers() const {
			ResourceList all = get_resource_records();
			ResourceList::const_iterator start_of_answers = all.begin();
			return ResourceList(start_of_answers, start_of_answers + get_answer_count());

		}

		const ResourceList get_nameservers() const {
			ResourceList all = get_resource_records();
			ResourceList::const_iterator start_of_nameservers = all.begin() + get_answer_count();
			return ResourceList(start_of_nameservers, start_of_nameservers + get_nameserver_count());
		}

		const ResourceList get_additionals() const {
			ResourceList all = get_resource_records();
			ResourceList::const_iterator start_of_additionals = all.begin() + get_answer_count() + get_nameserver_count();
			return ResourceList(start_of_additionals, start_of_additionals + get_additional_count());
		}

		const ResourceList get_resource_records() const {
			return this->records;
		}

		size_t get_question_count() const {
			return qd_count.to_ulong();
		}

		size_t get_resource_record_count() const {
			return get_answer_count() + get_nameserver_count() + get_additional_count();
			//return get_resource_records().size();
		}
		
		size_t get_answer_count() const {
			return an_count.to_ulong();
		}

		size_t get_nameserver_count() const {
			return ns_count.to_ulong();
		}
		
		size_t get_additional_count() const {
			return ar_count.to_ulong();
		}

		size_t response_code() {
			return rcode.to_ulong();
		}
		
		bool is_authoritative() {
			return aa;
		}

		size_t get_id() const {
			return this->id.to_ulong();
		}

	private:
		// dont use
		DNS() { };
		// TODO maybe hide the implementation of bitset?
		std::bitset<GENERIC_HEADER_FIELD_LENGTH> id, qd_count, an_count, ns_count, ar_count;
		bool response, aa, tc, rd, ra;
		std::bitset<OPCODE_FIELD_LENGTH> opcode;
		std::bitset<Z_FIELD_LENGTH> z;
		std::bitset<RCODE_FIELD_LENGTH> rcode;
		QuestionList questions;
		ResourceList records;
		
};

#endif /* !__domain__dns_h__ */

