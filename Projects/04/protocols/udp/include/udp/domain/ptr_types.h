/*
 * ptr_types.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef UDP_PTR_TYPES_H
#define UDP_PTR_TYPES_H

#include <boost/shared_ptr.hpp>
#include <boost/optional.hpp>

class Udp;

typedef   boost::shared_ptr<Udp>    UdpPtr;
typedef   boost::optional<Udp>      UdpMaybe;
typedef   boost::optional<UdpPtr>   UdpMaybePtr;

#endif /* !UDP_PTR_TYPES_H */

