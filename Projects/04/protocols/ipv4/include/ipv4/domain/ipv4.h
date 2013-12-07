/*
 * ipv4.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef IPV4_H
#define IPV4_H

#include <bitset>
#include "networkmuncher/util/byte/byte.h"
#include "networkmuncher/util/byte/convert.h"
#include "networkmuncher/util/logging.h"
#include "networkmuncher/domain/network_layer_protocol.h"

struct Ipv4 : public Logging, public NetworkLayerProtocol {
	public:

		virtual int what_type() const { return PType::Network::IPV4; }

		static const size_t EXPECTED_VERSION = 4;

		virtual size_t size() const { return header_length.to_ulong() * BITS_PER_BYTE * 4 + options.size(); }

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
		static const size_t ADDR_LENGTH                  =  32;

		static const size_t ADDR_LENGTH_IN_BYTES = ADDR_LENGTH / BITS_PER_BYTE;

		/**
		 * Offsets for flags
		 */
		static const size_t DONT_FRAGMENT_POS_FROM_LEFT  =  1;
		static const size_t MORE_FRAGMENTS_POS_FROM_LEFT =  2;
		static const size_t MORE_FRAGMENTS_POS_FROM_RIGHT = 0;

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
		typedef   std::bitset<ADDR_LENGTH>            Addr;
		typedef   BytesContainer                      Options;

		/**
		 * Ipv4 instance variables
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
		Addr           source_addr;
		Addr           dest_addr;
		Options        options;

		friend class Ipv4Builder;

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
			object << "source addr: " << addr_from_data(source_addr) << list_sep;
			object << "dest addr: " << addr_from_data(dest_addr) << list_sep;
			object << "options: " << "NOT SHOWN" << sep;

			return object.str();
		}

		bool is_fragmented() const {
			return flags[MORE_FRAGMENTS_POS_FROM_RIGHT];
		}

		bool operator==( const Ipv4& other ) const {
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

		static inline std::string addr_from_data( const BytesContainer& data ) {
			std::stringstream joined;

			for( size_t i = 0; i < ADDR_LENGTH_IN_BYTES; ++i ) {
				if( ! (i  < data.size()) ) {
					throw "Unexpected end of data while parsing ip";
				}

				joined << (size_t) data.at(i);

				if( i != ADDR_LENGTH_IN_BYTES - 1 ) {
					joined << ".";
				}

			}

			return joined.str();

		}

		static inline std::string addr_from_data( const std::bitset<ADDR_LENGTH>& data ) {
			return addr_from_data( convert_big_endian<ADDR_LENGTH_IN_BYTES>(data));
		}

    // TODO make protected
    //	protected:
		Ipv4() {}


};

#endif /* !IPV4_H */

