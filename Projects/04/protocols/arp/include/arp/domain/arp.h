/*
 * arp.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ARP_H
#define ARP_H

#include <bitset>
#include "networkmuncher/util/byte/byte.h"
#include "networkmuncher/util/logging.h"
#include "networkmuncher/domain/all.h"


struct Arp : public NetworkLayerProtocol, public Logging {
	public:
		typedef NetworkLayerProtocol InheritedProtocol;
		typedef NetworkLayerProtocolPtr InheritedProtocolPtr;
		typedef NetworkLayerProtocolMaybePtr InheritedProtocolMaybePtr;

		static const size_t HARDWARE_TYPE_LENGTH = 2*BITS_PER_BYTE;
		static const size_t PROTOCOL_TYPE_LENGTH = 2*BITS_PER_BYTE;
		static const size_t HARDWARE_SIZE_LENGTH = BITS_PER_BYTE;
		static const size_t PROTOCOL_SIZE_LENGTH = BITS_PER_BYTE;
		static const size_t OPCODE_LENGTH = 2*BITS_PER_BYTE;

		typedef std::bitset<HARDWARE_TYPE_LENGTH> HardwareType;
		typedef std::bitset<PROTOCOL_TYPE_LENGTH> ProtocolType;
		typedef std::bitset<HARDWARE_SIZE_LENGTH> HardwareSize;
		typedef std::bitset<PROTOCOL_SIZE_LENGTH> ProtocolSize;
		typedef MacAddr HardwareAddress;
		typedef std::bitset<IP_ADDR::BYTE_LENGTH * BITS_PER_BYTE> ProtocolAddress;

		HardwareType hardware_type;
		ProtocolType protocol_type;
		HardwareSize hardware_size;
		ProtocolSize protocol_size;
		HardwareAddress sender_hardware_address;
		ProtocolAddress sender_protocol_address;
		HardwareAddress target_hardware_address;
		ProtocolAddress target_protocol_address;

		friend class ArpBuilder;

		virtual int what_type() const { return PType::Network::ARP; }

		virtual std::string stringify_object() const {
			std::stringstream object;
			object << "TODO";
			return object.str();
		}

		bool operator==( const Arp& other ) const {
			return
				hardware_type == other.hardware_type &&
				protocol_type == other.protocol_type &&
				hardware_size == other.hardware_size &&
				protocol_size == other.protocol_size &&
				sender_hardware_address == other.sender_hardware_address &&
				sender_protocol_address == other.sender_protocol_address &&
				target_hardware_address == other.target_hardware_address &&
				target_protocol_address == other.target_protocol_address &&
				true;
		}

		Arp(
			const HardwareType& hardware_type,
			const ProtocolType& protocol_type,
			const HardwareSize& hardware_size,
			const ProtocolSize& protocol_size,
			const HardwareAddress& sender_hardware_address,
			const ProtocolAddress& sender_protocol_address,
			const HardwareAddress& target_hardware_address,
			const ProtocolAddress& target_protocol_address
			 ) : 
			hardware_type(hardware_type),
			protocol_type(protocol_type),
			hardware_size(hardware_size),
			protocol_size(protocol_size),
			sender_hardware_address(sender_hardware_address),
			sender_protocol_address(sender_protocol_address),
			target_hardware_address(target_hardware_address),
			target_protocol_address(target_protocol_address) {}

	protected:
		Arp() {}


};

#endif /* !ARP_H */

