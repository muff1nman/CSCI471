/*
 * parsers.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef PARSERS_H
#define PARSERS_H

#include <map>

#include "ethernet/parse/ethernet.h"
#include "icmp/parse/ip.h"
#include "icmp/parse/echo.h"
#include "udp/parse/udp.h"
#include "dns/parse/dns.h"
#include "parser_types.h"
#include "networkmuncher/domain/protocol_types.h"

NetworkParseFunction ip_parser = &IP::from_data_as_ptr;

std::map<int, NetworkParser> network_parsers = boost::assign::map_list_of
(PType::Network::IPV4, ip_parser);

LinkParseFunction ethernet_v2 = &ETHERNETV2::from_data_as_ptr;
LinkParseFunction ethernet_8023 = &ETHERNET8023::from_data_as_ptr;

std::map<int,LinkParser> link_parsers = boost::assign::map_list_of
(PType::Link::ETHERNET_V2, ethernet_v2)
(PType::Link::ETHERNET_8023, ethernet_8023);

TransportParseFunction icmp = &ECHO::from_data_as_ptr;
TransportParseFunction udp = &UDP::from_data_as_ptr;

std::map<int,TransportParser> transport_parsers = boost::assign::map_list_of
(PType::Transport::ICMP_ECHO,icmp)
(PType::Transport::UDP, udp);

ApplicationParseFunction dns = &from_data_as_ptr; // TODO nest in namespace
std::map<int,ApplicationParser> application_parsers = boost::assign::map_list_of
(PType::Application::DNS, dns);


#endif /* !PARSERS_H */

