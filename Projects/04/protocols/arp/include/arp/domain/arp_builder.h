/*
 * arp_builder.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ARP_BUILDER_H
#define ARP_BUILDER_H

#include "arp.h"
#include "ptr_types.h"

#include "networkmuncher/util/byte/byte.h"
class ArpBuilder {

	public:
		ArpBuilder& set_hardware_type(const Arp::HardwareType& type) {
			this->hardware_type = type;
			return do_common();
		}

		ArpBuilder& set_protocol_type(const Arp::ProtocolType& type) {
			this->protocol_type = type;
			return do_common();
		}
		
		ArpBuilder& set_hardware_size(const Arp::HardwareSize& size) {
			this->hardware_size = size;
			return do_common();
		}
		
		ArpBuilder& set_protocol_size(const Arp::ProtocolSize& size) {
			this->protocol_size = size;
			return do_common();
		}
		
		ArpBuilder& set_sender_hardware_address(const Arp::HardwareAddress addr) {
			this->sender_hardware_address = addr;
			return do_common();
		}

		ArpBuilder& set_sender_protocol_address(const Arp::ProtocolAddress addr) {
			this->sender_protocol_address = addr;
			return do_common();
		}
		
		ArpBuilder& set_target_hardware_address(const Arp::HardwareAddress addr) {
			this->target_hardware_address = addr;
			return do_common();
		}
		
		ArpBuilder& set_target_protocol_address(const Arp::ProtocolAddress addr) {
			this->target_protocol_address = addr;
			return do_common();
		}

		virtual Arp build() {
			set_default_fields();
			return Arp(hardware_type, protocol_type, hardware_size,
				protocol_size, sender_hardware_address,
				sender_protocol_address,target_hardware_address, 
				target_protocol_address);
 }

		virtual ArpPtr build_ptr() {
			set_default_fields();
			return ArpPtr( new Arp(hardware_type, protocol_type,
				hardware_size, protocol_size, sender_hardware_address, sender_protocol_address,
				target_hardware_address, target_protocol_address));
		}

		virtual ~ArpBuilder() { }

	protected:
		Arp::HardwareType hardware_type;
		Arp::ProtocolType protocol_type;
		Arp::HardwareSize hardware_size;
		Arp::ProtocolSize protocol_size;
		Arp::HardwareAddress sender_hardware_address;
		Arp::ProtocolAddress sender_protocol_address;
		Arp::HardwareAddress target_hardware_address;
		Arp::ProtocolAddress target_protocol_address;

		ArpBuilder& do_common() {
			return *this;
		}

		void set_default_fields() {} // TODO, allow length and checksum to be calculated

};

#endif /* !ARP_BUILDER_H */

