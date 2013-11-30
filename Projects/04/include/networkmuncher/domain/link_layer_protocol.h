/*
 * link_layer_protocol.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef LINK_LAYER_PROTOCOL_H
#define LINK_LAYER_PROTOCOL_H

#include "protocol.h"

class LinkLayerProtocol : public Protocol {
	public:
		static const int UNKNOWN_LINK_LAYER_PROTOCOL = 100;

		virtual int what_type() {
			return UNKNOWN_LINK_LAYER_PROTOCOL;
		}

};

#endif /* !LINK_LAYER_PROTOCOL_H */

