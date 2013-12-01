/*
 * echo.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef DOMAIN_ECHO_H
#define DOMAIN_ECHO_H

#include "networkmuncher/util/byte/byte.h"
#include "networkmuncher/util/byte/print.h"
#include "networkmuncher/util/logging.h"
#include "networkmuncher/domain/all.h"

struct Echo : public TransportLayerProtocol, public Logging {
	public:

		virtual int what_type() const { return PType::Transport::ICMP_ECHO; }
		static const size_t TYPE_LENGTH         = 8;
		static const size_t CODE_LENGTH         = 8;
		static const size_t CHECKSUM_LENGTH     = 16;
		static const size_t IDENTIFIER_LENGTH   = 16;
		static const size_t SEQUENCE_NUM_LENGTH = 16;

		typedef std::bitset<TYPE_LENGTH>           Type;
		typedef std::bitset<CODE_LENGTH>           Code;
		typedef std::bitset<CHECKSUM_LENGTH>       Checksum;
		typedef std::bitset<IDENTIFIER_LENGTH>     Identifier;
		typedef std::bitset<SEQUENCE_NUM_LENGTH>   SequenceNum;
		typedef BytesContainer                     Data;

		Type          type;
		Code          code;
		Checksum      checksum;
		Identifier    identifier;
		SequenceNum   sequence_num;
		Data          data;

		friend class EchoBuilder;

		std::string stringify_object() const {
			std::stringstream object;
			object << "type: " << type.to_ulong() << list_sep;
			object << "code: " << code.to_ulong() << list_sep;
			object << "checksum: " << checksum.to_ulong() << list_sep;
			object << "identifier: " << identifier.to_ulong() << list_sep;
			object << "seq num: " << sequence_num.to_ulong() << list_sep;
			object << "data:\n" << demaria_util::to_string(data) << "\n";
			return object.str();
		}

		bool operator==(const Echo& other) const {
			return
				type         == other.type         &&
				code         == other.code         &&
				checksum     == other.checksum     &&
				identifier   == other.identifier   &&
				sequence_num == other.sequence_num &&
				data         == other.data         &&
				true;
		}

	protected:
		// zerod out
		Echo() {
			type = Type(0);
			code = Code(0);
			checksum = Checksum(0);
			identifier = Identifier(0);
			sequence_num = SequenceNum(0);
			data = Data();
		}

};

#endif /* !DOMAIN_ECHO_H */

