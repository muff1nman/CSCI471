/*
 * transport_layer_protocol.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef TRANSPORT_LAYER_PROTOCOL_H
#define TRANSPORT_LAYER_PROTOCOL_H

#include "protocol.h"

class TransportLayerProtocol : public Protocol {
	public:
		static const int UNKNOWN_TRANSPORT_LAYER_PROTOCOL = 300;

		virtual int what_type() {
			return UNKNOWN_TRANSPORT_LAYER_PROTOCOL;
		}

};

#endif /* !TRANSPORT_LAYER_PROTOCOL_H */

