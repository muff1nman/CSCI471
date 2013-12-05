/*
 * ptr_types.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ARP_PTR_TYPES_H
#define ARP_PTR_TYPES_H

#include <boost/shared_ptr.hpp>
#include <boost/optional.hpp>

class Arp;

typedef   boost::shared_ptr<Arp>    ArpPtr;
typedef   boost::optional<Arp>      ArpMaybe;
typedef   boost::optional<ArpPtr>   ArpMaybePtr;

#endif /* !ARP_PTR_TYPES_H */

