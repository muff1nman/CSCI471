/*
 * ptr_types.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef TCP_PTR_TYPES_H
#define TCP_PTR_TYPES_H

#include <boost/shared_ptr.hpp>
#include <boost/optional.hpp>

class Tcp;

typedef   boost::shared_ptr<Tcp>    TcpPtr;
typedef   boost::optional<Tcp>      TcpMaybe;
typedef   boost::optional<TcpPtr>   TcpMaybePtr;

#endif /* !TCP_PTR_TYPES_H */

