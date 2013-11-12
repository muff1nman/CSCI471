/*
 * ptr_types.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef PTR_TYPES_H
#define PTR_TYPES_H

#include <boost/shared_ptr.hpp>

class Raw;
class Echo;
class Ip;

typedef boost::shared_ptr<Raw> RawPtr;
typedef boost::shared_ptr<Echo> EchoPtr;
typedef boost::shared_ptr<Ip> IpPtr;

#endif /* !PTR_TYPES_H */

