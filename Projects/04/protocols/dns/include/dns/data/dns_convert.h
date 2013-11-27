/*
 * dns_convert.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_dns_convert_h__
#define __dns_dns_convert_h__


#include "networkmuncher/data/convert.h"

#include "dns/domain/dns.h"

#include <boost/shared_ptr.hpp>

class DNSConvert : public Convert {

	public:
		DNSConvert(boost::shared_ptr<DNS> dns) : dns(dns) { }
		virtual BytesContainer to_data() const;

	private:
		boost::shared_ptr<DNS> dns;
		std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH> flags() const;
};

#endif /* !__dns_dns_convert_h__ */

