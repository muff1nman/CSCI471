/*
 * parsers.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef PARSERS_H
#define PARSERS_H

#include <set>

#include "ethernet/parse/ethernet.h"
#include "icmp/parse/ip.h"
#include "parser_types.h"

NetworkParseFunction ip_parser = &IP::from_data_as_ptr;

std::vector<NetworkParser> network_parsers = boost::assign::list_of
(ip_parser);

LinkParseFunction ethernet_v2 = &ETHERNETV2::from_data_as_ptr;
LinkParseFunction ethernet_8023 = &ETHERNET8023::from_data_as_ptr;

std::vector<LinkParser> link_parsers = boost::assign::list_of
(ethernet_v2)(ethernet_8023);

#endif /* !PARSERS_H */

