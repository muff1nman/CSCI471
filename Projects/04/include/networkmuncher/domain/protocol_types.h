/*
 * protocol_types.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef PROTOCOL_TYPES_H
#define PROTOCOL_TYPES_H

namespace PType {

	const static int APPLICATION = 400;
	namespace Application {
		const static int DNS = 401;
	}

	const static int TRANSPORT =  300;
	namespace Transport {
		const static int ICMP_ECHO  = 301; // TODO move to network layer?
		const static int UDP = 302;
		const static int TCP = 303;
	}

	const static int NETWORK = 200;
	namespace Network {
		const static int IPV4 = 201;
		const static int IPV6 = 202;
		const static int ARP = 203;
	}

	const static int LINK = 100;
	namespace Link {
		const static int ETHERNET_UNKNOWN = 101;
		const static int ETHERNET_V2 = 102;
		const static int ETHERNET_8023 = 103;
	}

	const static int UNKNOWN = 0;
}

#endif /* !PROTOCOL_TYPES_H */

