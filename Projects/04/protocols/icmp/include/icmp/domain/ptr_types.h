/*
 * ptr_types.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ICMP_PTR_TYPES_H
#define ICMP_PTR_TYPES_H

#include <boost/shared_ptr.hpp>

class Raw;
class Echo;

typedef boost::shared_ptr<Raw> RawPtr;
typedef boost::shared_ptr<Echo> EchoPtr;

#endif /* !ICMP_PTR_TYPES_H */

