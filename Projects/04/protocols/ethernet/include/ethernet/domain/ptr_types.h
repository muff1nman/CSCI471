/*
 * ptr_types.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ETHERNET_PTR_TYPES_H
#define ETHERNET_PTR_TYPES_H

#include <boost/shared_ptr.hpp>
#include <boost/optional.hpp>

class Ethernet;

typedef   boost::shared_ptr<Ethernet>    EthernetPtr;
typedef   boost::optional<Ethernet>      EthernetMaybe;
typedef   boost::optional<EthernetPtr>   EthernetMaybePtr;

#endif /* !ETHERNET_PTR_TYPES_H */

