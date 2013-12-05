/*
 * tcp_builder.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef TCP_BUILDER_H
#define TCP_BUILDER_H

#include "tcp.h"
#include "ptr_types.h"

#include "networkmuncher/util/byte/byte.h"
class TcpBuilder {

	public:
		TcpBuilder& set_source_port(const Tcp::Port& port) {
			this->source_port = port;
			return do_common();
		}

		TcpBuilder& set_dest_port(const Tcp::Port& port) {
			this->dest_port = port;
			return do_common();
		}

		TcpBuilder& set_seq_num(const Tcp::SynAck& synack) {
			this->seq_num = synack;
			return do_common();
		}

		TcpBuilder& set_ack_num(const Tcp::SynAck& synack) {
			this->ack_num = synack;
			return do_common();
		}

		TcpBuilder& set_data_offset(const Tcp::DataOffset& offset) {
			this->data_offset = offset;
			return do_common();
		}

		TcpBuilder& set_reserved(const Tcp::Reserved& reserved) {
			this->reserved = reserved;
			return do_common();
		}

		TcpBuilder& set_flags(const Tcp::Flags& flags) {
			this->flags = flags;
			return do_common();
		}

		TcpBuilder& set_window_size(const Tcp::WindowSize& window) {
			this->window_size = window;
			return do_common();
		}

		TcpBuilder& set_checksum(const Tcp::Checksum& checksum) {
			this->checksum = checksum;
			return do_common();
		}

		TcpBuilder& set_urgent(const Tcp::Urgent& urgent) {
			this->urgent = urgent;
			return do_common();
		}

		TcpBuilder& set_options(const Tcp::Options& options) {
			this->options = options;
			return do_common();
		}

		virtual Tcp build() {
			set_default_fields();
			return Tcp(source_port, dest_port, seq_num, ack_num, data_offset,
					reserved, flags, window_size, checksum, urgent, options);
 }

		virtual TcpPtr build_ptr() {
			set_default_fields();
			return TcpPtr( new Tcp(source_port, dest_port, seq_num, ack_num,
						data_offset, reserved, flags, window_size, checksum, urgent,
						options));
		}

		virtual ~TcpBuilder() { }

	protected:
		Tcp::Port source_port;
		Tcp::Port dest_port;
		Tcp::SynAck seq_num;
		Tcp::SynAck ack_num;
		Tcp::DataOffset data_offset;
		Tcp::Reserved reserved;
		Tcp::Flags flags;
		Tcp::WindowSize window_size;
		Tcp::Checksum checksum;
		Tcp::Urgent urgent;
		Tcp::Options options;

		TcpBuilder& do_common() {
			return *this;
		}

		void set_default_fields() {} // TODO, allow length and checksum to be calculated

};

#endif /* !TCP_BUILDER_H */

