/*
 * dns.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_h__
#define __dns_h__

#include "dns/domain/dns.h"

#include "networkmuncher/socket/socket.h"

#include <boost/shared_ptr.hpp>
#include <boost/optional.hpp>
#include <string>
#include <vector>

static const char* ROOT_SERVER = "198.41.0.4";

typedef   boost::shared_ptr<DNS>      DnsPtr;
typedef   boost::optional<DnsPtr>     DnsMaybePtr;
typedef   std::string                 NameOrIp;
typedef   boost::optional<NameOrIp>   MaybeNameOrIp;
typedef   std::vector<NameOrIp>       ListNameOrIp;

/**
 * This family of functions are just some handy functions for filtering out
 * results.
 */
// TODO the argument name should not be query but response
ListNameOrIp    filter_ips         ( DnsPtr query );
MaybeNameOrIp   filter_first_ip    ( DnsPtr query );
ListNameOrIp    filter_nameservers ( DnsPtr query );
MaybeNameOrIp   filter_first_ns    ( DnsPtr query );
ListNameOrIp    filter_cnames      ( DnsPtr query );
MaybeNameOrIp   filter_first_cname ( DnsPtr query );

/**
 * Send and Receive a single query (i.e. not recursive).  If there was an error
 * the return result is not instaniated (see boost::optional).  Server must be
 * a valid ip address of the form XXX.XXX.XXX.XXX. Print intermeidate is not
 * really as relevant here (as it is not recursive) but it makes the api look
 * nice :)
 */
DnsMaybePtr send_and_receive                  ( const std::string& server, DnsPtr query, Socket& socket, bool print_intermediate = false );
/**
 * This is really an internal function as it bypasses caching, but exposed here just in case you want
 * to use it.  Note that in order for this function to work correctly server
 * should really be an ip address for a root server.
 */
DnsMaybePtr recursive_send_and_recieve        ( const std::string& server, DnsPtr query, Socket& socket, bool print_intermediate = false );

/**
 *  Send a query to the given server ip address, but if there is no reponse
 *  begin a recursive send and receive starting with the root servers. Note that
 *  this function may use caching if enabled.
 */
DnsMaybePtr query_once_and_then_try_recursive ( const std::string& server, DnsPtr query, Socket& socket, bool print_intermediate = false );

#endif /* !__dns_h__ */

