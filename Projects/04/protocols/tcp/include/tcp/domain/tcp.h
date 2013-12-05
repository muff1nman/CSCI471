/*
 * tcp.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef TCP_H
#define TCP_H

#include <bitset>
#include "networkmuncher/util/byte/byte.h"
#include "networkmuncher/util/logging.h"
#include "networkmuncher/domain/all.h"


struct Tcp : public TransportLayerProtocol, public Logging {
	public:
		typedef TransportLayerProtocol InheritedProtocol;
		typedef TransportLayerProtocolPtr InheritedProtocolPtr;
		typedef TransportLayerProtocolMaybePtr InheritedProtocolMaybePtr;

		static const size_t PORT_LENGTH = 2*BITS_PER_BYTE;
		static const size_t SYNACK_NUM_LENGTH = 4*BITS_PER_BYTE;
		static const size_t DATA_OFFSET_LENGTH = 3;
		static const size_t RESERVED_LENGTH = 3;
		static const size_t FLAGS_LENGTH = 9;
		static const size_t WINDOW_SIZE_LENGTH = 2*BITS_PER_BYTE;
		static const size_t CHECKSUM_LENGTH = 2*BITS_PER_BYTE;
		static const size_t URGENT_LENGTH = 2*BITS_PER_BYTE;

		typedef std::bitset<PORT_LENGTH> Port;
		typedef std::bitset<SYNACK_NUM_LENGTH> SynAck;
		typedef std::bitset<DATA_OFFSET_LENGTH> DataOffset;
		typedef std::bitset<RESERVED_LENGTH> Reserved;
		typedef std::bitset<FLAGS_LENGTH> Flags;
		typedef std::bitset<WINDOW_SIZE_LENGTH> WindowSize
		typedef std::bitset<CHECKSUM_LENGTH> Checksum;
		typedef std::bitset<URGENT_LENGTH> Urgent;
		typedef BytesContainer Options;

		Port source_port;
		Port dest_port;
		SynAck seq_num;
		SynAck ack_num;
		DataOffset data_offset;
		Reserved reserved;
		Flags flags;
		WindowSize window_size;
		Checksum checksum;
		Urgent urgent;
		Options options;

		friend class TcpBuilder;

		virtual int what_type() const { return PType::Transport::TCP; }

		virtual std::string stringify_object() const {
			std::stringstream object;
			object << "TODO";
			return object.str();
		}

		bool operator==( const Tcp& other ) const {
			return
				source_port == other.source_port &&
				dest_port == other.dest_port &&
				seq_num == other.seq_num &&
				ack_num == other.ack_num &&
				data_offset == other.data_offset &&
				reserved == other.reserved &&
				flags == other.flags &&
				window_size == other.window_size &&
				checksum == other.checksum &&
				urgent == other.urgent &&
				options == other.options &&
				true;
		}


		Tcp(
			const Port& source_port,
			const Port& dest_port,
			const SynAck& seq_num,
			const SynAck& ack_num,
			const DataOffset& data_offset,
			const Reserved& reserved,
			const Flags& flags,
			const WindowSize& window_size,
			const Checksum& checksum,
			const Urgent& urgent,
			const Options& options
			 ) : 
			source_port(source_port),
			dest_port(dest_port),
			seq_num(seq_num),
			ack_num(ack_num),
			data_offset(data_offset),
			reserved(reserved),
			flags(flags),
			window_size(window_size),
			checksum(checksum),
			urgent(urgent),
			options(options) {}

	protected:
		Tcp() {}


};

#endif /* !TCP_H */

