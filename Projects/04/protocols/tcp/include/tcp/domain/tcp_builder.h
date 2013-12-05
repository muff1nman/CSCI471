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
		TcpBuilder& set_hardware_type(const Tcp::HardwareType& type) {
			this->hardware_type = type;
			return do_common();
		}

		TcpBuilder& set_protocol_type(const Tcp::ProtocolType& type) {
			this->protocol_type = type;
			return do_common();
		}
		
		TcpBuilder& set_hardware_size(const Tcp::HardwareSize& size) {
			this->hardware_size = size;
			return do_common();
		}
		
		TcpBuilder& set_protocol_size(const Tcp::ProtocolSize& size) {
			this->protocol_size = size;
			return do_common();
		}
		
		TcpBuilder& set_sender_hardware_address(const Tcp::HardwareAddress addr) {
			this->sender_hardware_address = addr;
			return do_common();
		}

		TcpBuilder& set_sender_protocol_address(const Tcp::ProtocolAddress addr) {
			this->sender_protocol_address = addr;
			return do_common();
		}
		
		TcpBuilder& set_target_hardware_address(const Tcp::HardwareAddress addr) {
			this->target_hardware_address = addr;
			return do_common();
		}
		
		TcpBuilder& set_target_protocol_address(const Tcp::ProtocolAddress addr) {
			this->target_protocol_address = addr;
			return do_common();
		}

		virtual Tcp build() {
			set_default_fields();
			return Tcp(hardware_type, protocol_type, hardware_size,
				protocol_size, sender_hardware_address,
				sender_protocol_address,target_hardware_address, 
				target_protocol_address);
 }

		virtual TcpPtr build_ptr() {
			set_default_fields();
			return TcpPtr( new Tcp(hardware_type, protocol_type,
				hardware_size, protocol_size, sender_hardware_address, sender_protocol_address,
				target_hardware_address, target_protocol_address));
		}

		virtual ~TcpBuilder() { }

	protected:
		Tcp::HardwareType hardware_type;
		Tcp::ProtocolType protocol_type;
		Tcp::HardwareSize hardware_size;
		Tcp::ProtocolSize protocol_size;
		Tcp::HardwareAddress sender_hardware_address;
		Tcp::ProtocolAddress sender_protocol_address;
		Tcp::HardwareAddress target_hardware_address;
		Tcp::ProtocolAddress target_protocol_address;

		TcpBuilder& do_common() {
			return *this;
		}

		void set_default_fields() {} // TODO, allow length and checksum to be calculated

};

#endif /* !TCP_BUILDER_H */

