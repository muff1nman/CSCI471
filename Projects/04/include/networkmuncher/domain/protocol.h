/*
 * protocol.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef PROTOCOL_H
#define PROTOCOL_H

class Protocol {
	public:
		const static int UNKNOWN_PROTOCOL = 0;

		virtual int what_type() const {
			return UNKNOWN_PROTOCOL;
		}

};

#endif /* !PROTOCOL_H */

