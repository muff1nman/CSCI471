/*
 * ptr_types.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef IPV6_PTR_TYPES_H
#define IPV6_PTR_TYPES_H

#include <boost/shared_ptr.hpp>
#include <boost/optional.hpp>

class Ipv6;

typedef   boost::optional<Ipv6>        Ipv6Maybe;
typedef   boost::shared_ptr<Ipv6>      Ipv6Ptr;
typedef   boost::optional<Ipv6Ptr>     Ipv6MaybePtr;


#endif /* !IPV6_PTR_TYPES_H */

