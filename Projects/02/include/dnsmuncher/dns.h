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

static const char* ROOT_SERVER = "198.41.0.4";

typedef   boost::shared_ptr<DNS>      DnsPtr;
typedef   std::string                 NameOrIp;
typedef   boost::optional<NameOrIp>   MaybeNameOrIp;
typedef   std::vector<NameOrIp>       ListNameOrIp;

ListNameOrIp    filter_ips         ( DnsPtr query );
MaybeNameOrIp   filter_first_ip    ( DnsPtr query );
ListNameOrIp    filter_nameservers ( DnsPtr query );
MaybeNameOrIp   filter_first_ns    ( DnsPtr query );
ListNameOrIp    filter_cnames      ( DnsPtr query );
MaybeNameOrIp   filter_first_cname ( DnsPtr query );

DnsPtr send_and_receive                  ( const std::string& server, DnsPtr query );
DnsPtr recursive_send_and_recieve        ( const std::string& server, DnsPtr query );
DnsPtr query_once_and_then_try_recursive ( const std::string& server, DnsPtr query );

#endif /* !__dns_h__ */

