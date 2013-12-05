/*
 * ptr_types.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef IPV4_PTR_TYPES_H
#define IPV4_PTR_TYPES_H

#include <boost/shared_ptr.hpp>
#include <boost/optional.hpp>

class Ipv4;

typedef   boost::optional<Ipv4>        Ipv4Maybe;
typedef   boost::shared_ptr<Ipv4>      Ipv4Ptr;
typedef   boost::optional<Ipv4Ptr>     Ipv4MaybePtr;


#endif /* !IPV4_PTR_TYPES_H */

