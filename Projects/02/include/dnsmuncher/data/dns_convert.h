/*
 * dns_convert.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_convert_h__
#define __dns_convert_h__

#include "dnsmuncher/domain/dns"

class DNSConvert : public Convert, public DNS {
	virtual Bytes to_data() const;
};

#endif /* !__dns_convert_h__ */

