/*
 * application_layer_protocol.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef APPLICATION_LAYER_PROTOCOL_H
#define APPLICATION_LAYER_PROTOCOL_H

#include "protocol.h"

class ApplicationLayerProtocol : public Protocol {
	public:
		static const int UNKNOWN_APPLICATION_LAYER_PROTOCOL = 400;

		virtual int what_type() {
			return UNKNOWN_APPLICATION_LAYER_PROTOCOL;
		}

};

#endif /* !APPLICATION_LAYER_PROTOCOL_H */

