/*
 * ipv6.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef IPV6_H
#define IPV6_H

#include <bitset>
#include "networkmuncher/util/byte/byte.h"
#include "networkmuncher/util/byte/convert.h"
#include "networkmuncher/util/logging.h"
#include "networkmuncher/domain/network_layer_protocol.h"

struct Ipv6 : public Logging, public NetworkLayerProtocol {
	public:

		virtual int what_type() const { return PType::Network::IPV6; }

		static const size_t EXPECTED_VERSION = 6;

		/**
		 * Lengths for bitsets
		 */
		static const size_t VERSION_LENGTH               =  4;
		static const size_t TOS_LENGTH                   =  8;
		static const size_t FLOW_LENGTH                  =  20;
		static const size_t TOTAL_LENGTH_LENGTH          =  16;
		static const size_t NEXT_HEADER_LENGTH           =  8;
		static const size_t HOP_LIMIT_LENGTH             =  8;
		static const size_t ADDR_LENGTH                  =  128;

		static const size_t ADDR_LENGTH_IN_BYTES = ADDR_LENGTH / BITS_PER_BYTE;

		/**
		 * Types
		 */
		typedef   std::bitset<VERSION_LENGTH>         Version;
		typedef   std::bitset<TOS_LENGTH>             Tos;
		typedef   std::bitset<FLOW_LENGTH>            Flow;
		typedef   std::bitset<TOTAL_LENGTH_LENGTH>    TotalLength;
		typedef   std::bitset<NEXT_HEADER_LENGTH>     NextHeader;
		typedef   std::bitset<HOP_LIMIT_LENGTH>       HopLimit;
		typedef   std::bitset<ADDR_LENGTH>            Addr;

		/**
		 * Ipv6 instance variables
		 */
		Version        version;
		Tos            tos;
		Flow           flow;
		TotalLength    total_length;
		NextHeader     next_header;
		HopLimit       hop_limit;
		Addr           source_addr;
		Addr           dest_addr;

		friend class Ipv6Builder;

		std::string stringify_object() const {
			std::stringstream object;
			object << "Todo";

			return object.str();
		}

		bool operator==( const Ipv6& other ) const {
			return
				version == other.version &&
				tos == other.tos &&
				flow == other.flow &&
				total_length == other.total_length &&
				next_header == other.next_header &&
				hop_limit == other.hop_limit &&
				source_addr == other.source_addr &&
				dest_addr == other.dest_addr &&
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
		Ipv6() {}


};

#endif /* !IPV6_H */

