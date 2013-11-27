/*
 * convert.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_convert_h__
#define __dns_convert_h__

#include "networkmuncher/util/byte/byte.h"

class Convert {
	public:
		virtual BytesContainer to_data() const = 0;

		virtual ~Convert() { }
};

#endif /* !__dns_convert_h__ */

