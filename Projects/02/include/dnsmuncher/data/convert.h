/*
 * convert.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __convert_h__
#define __convert_h__

#include "dnsmuncher/util/byte/byte.h"

class Convert {
	public:
		virtual BytesContainer to_data() const = 0;
};

#endif /* !__convert_h__ */

