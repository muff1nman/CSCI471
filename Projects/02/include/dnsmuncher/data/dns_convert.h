/*
 * dns_convert.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_convert_h__
#define __dns_convert_h__

#include "dnsmuncher/domain/dns.h"
#include "convert.h"

#include <boost/shared_ptr.hpp>

class DNSConvert : public Convert {

	public:
		DNSConvert(boost::shared_ptr<DNS> dns);
		virtual BytesContainer to_data() const;

	private:
		boost::shared_ptr<DNS> dns;
};

#endif /* !__dns_convert_h__ */

