/*
 * network_layer_protocol.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef NETWORK_LAYER_PROTOCOL_H
#define NETWORK_LAYER_PROTOCOL_H

#include "protocol.h"

class NetworkLayerProtocol : public Protocol {
	public:

		virtual int what_type() const {
			return PType::NETWORK;
		}

};

#endif /* !NETWORK_LAYER_PROTOCOL_H */

