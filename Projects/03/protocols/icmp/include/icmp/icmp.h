/*
 * icmp.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ICMP_H
#define ICMP_H

#include "icmp/domain/echo.h"

#include <boost/optional.hpp>

boost::optional<Echo> ping_and_pong_once( const std::string& dest_ip, const Echo& request );

#endif /* !ICMP_H */

