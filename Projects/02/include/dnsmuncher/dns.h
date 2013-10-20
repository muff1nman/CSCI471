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
#include <boost/optional.hpp>
#include <string>
#include <vector>

std::vector<std::string> filter_ips( boost::shared_ptr<DNS> query );
boost::optional<std::string> filter_first_ip( boost::shared_ptr<DNS> query );
std::vector<std::string> filter_nameservers( boost::shared_ptr<DNS> query );
boost::optional<std::string> filter_first_ns( boost::shared_ptr<DNS> query );
std::vector<std::string> filter_cnames( boost::shared_ptr<DNS> query );
boost::optional<std::string> filter_first_cname( boost::shared_ptr<DNS> query );

void send_and_receive( const std::string& server, boost::shared_ptr<DNS> query );

#endif /* !__dns_h__ */

