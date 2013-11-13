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

struct Ip {
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

	protected:
		Ip() {}


};

#endif /* !IP_H */

