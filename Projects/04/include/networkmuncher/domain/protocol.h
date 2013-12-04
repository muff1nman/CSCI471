/*
 * protocol.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "protocol_types.h"

class Protocol {
	public:

		virtual int what_type() const = 0;

		virtual size_t size() const { return 0; }

		virtual ~Protocol() { }

};

#endif /* !PROTOCOL_H */

