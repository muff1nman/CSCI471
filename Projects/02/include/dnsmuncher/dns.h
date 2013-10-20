/*
 * dns.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_h__
#define __dns_h__

#include "dnsmuncher/domain/dns.h"

#include <boost/shared_ptr.hpp>
#include <string>

void send_and_receive( const std::string& server, boost::shared_ptr<DNS> query );

#endif /* !__dns_h__ */

