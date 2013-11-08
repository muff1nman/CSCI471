/*
 * qtype.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_qtype_h__
#define __dns_qtype_h__

#include "type.h"

class QType : public Type {
	public:
		QType( size_t type = Type::A ) : Type(type) { }
};

#endif /* !__dns_qtype_h__ */

