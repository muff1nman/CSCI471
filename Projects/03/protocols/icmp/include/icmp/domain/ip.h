/*
 * ip.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef IP_H
#define IP_H

#include <bitset>
#include "networkmuncher/util/byte/byte.h"
#include "networkmuncher/util/logging.h"
#include "networkmuncher/parse/ip_addr.h"

struct Ip : public Logging {
	public:

		/**
		 * Lengths for bitsets
		 */
		static const size_t VERSION_LENGTH               =  4;
		static const size_t HEADER_LENGTH_LENGTH         =  4;
		static const size_t TOS_LENGTH                   =  8;
		static const size_t TOTAL_LENGTH_LENGTH          =  16;
		static const size_t ID_LENGTH                    =  16;
		static const size_t FLAGS_LENGTH                 =  3;
		static const size_t FRAG_OFFSET_LENGTH           =  13;
		static const size_t TTL_LENGTH                   =  8;
		static const size_t PROTOCOL_LENGTH              =  8;
		static const size_t CHECKSUM_LENGTH              =  16;
		static const size_t SOURCE_ADDR_LENGTH           =  32;
		static const size_t DEST_ADDR_LENGTH             =  32;

		/**
		 * Offsets for flags
		 */
		static const size_t DONT_FRAGMENT_POS_FROM_LEFT  =  1;
		static const size_t MORE_FRAGMENTS_POS_FROM_LEFT =  2;

		/**
		 * Types
		 */
		typedef   std::bitset<VERSION_LENGTH>         Version;
		typedef   std::bitset<HEADER_LENGTH_LENGTH>   HeaderLength;
		typedef   std::bitset<TOS_LENGTH>             Tos;
		typedef   std::bitset<TOTAL_LENGTH_LENGTH>    TotalLength;
		typedef   std::bitset<ID_LENGTH>              Id;
		typedef   std::bitset<FLAGS_LENGTH>           Flags;
		typedef   std::bitset<FRAG_OFFSET_LENGTH>     FragOffset;
		typedef   std::bitset<TTL_LENGTH>             TTL;
		typedef   std::bitset<PROTOCOL_LENGTH>        Protocol;
		typedef   std::bitset<CHECKSUM_LENGTH>        Checksum;
		typedef   std::bitset<SOURCE_ADDR_LENGTH>     SourceAddr;
		typedef   std::bitset<DEST_ADDR_LENGTH>       DestAddr;
		typedef   BytesContainer                      Options;

		/**
		 * Ip instance variables
		 */
		Version        version;
		HeaderLength   header_length;
		Tos            tos;
		TotalLength    total_length;
		Id             id;
		Flags          flags;
		FragOffset     frag_offset;
		TTL            ttl;
		Protocol       protocol;
		Checksum       checksum;
		SourceAddr     source_addr;
		DestAddr       dest_addr;
		Options        options;

		friend class IpBuilder;

		std::string stringify_object() const {
			std::stringstream object;
			object << "version: " << version.to_ulong() << list_sep;
			object << "header len: " << header_length.to_ulong() << list_sep;
			object << "tos: " << tos.to_ulong() << list_sep;
			object << "total length: " << total_length.to_ulong() << list_sep;
			object << "id: " << id.to_ulong() << list_sep;
			object << "flags: " << flags.to_string() << list_sep;
			object << "frag offset: " << frag_offset.to_ulong() << list_sep;
			object << "ttl: " << ttl.to_ulong() << list_sep;
			object << "protocol: " << protocol.to_ulong() << list_sep;
			object << "checksum: " << checksum.to_string() << list_sep;
			object << "source addr: " << ip_from_data(source_addr) << list_sep;
			object << "dest addr: " << ip_from_data(dest_addr) << list_sep;
			object << "options: " << "NOT SHOWN" << sep;

			return object.str();
		}

		bool operator==( const Ip& other ) const {
			return
				version       == other.version       &&
				header_length == other.header_length &&
				tos           == other.tos           &&
				total_length  == other.total_length  &&
				id            == other.id            &&
				flags         == other.flags         &&
				frag_offset   == other.frag_offset   &&
				ttl           == other.ttl           &&
				protocol      == other.protocol      &&
				checksum      == other.checksum      &&
				source_addr   == other.source_addr   &&
				dest_addr     == other.dest_addr     &&
				options       == other.options       &&
				true;
		}

	protected:
		Ip() {}


};

#endif /* !IP_H */

