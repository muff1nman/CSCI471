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

		virtual int what_type() const {
			return PType::LINK;
		}

};

#endif /* !LINK_LAYER_PROTOCOL_H */

