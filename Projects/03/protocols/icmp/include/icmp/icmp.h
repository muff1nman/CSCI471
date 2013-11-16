/*
 * icmp.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ICMP_H
#define ICMP_H

#include "icmp/domain/domain.h"

EchoMaybePtr ping_and_pong_once( const std::string& dest_ip );

#endif /* !ICMP_H */

