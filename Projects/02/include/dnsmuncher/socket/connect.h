/*
 * connect.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __connect_h__
#define __connect_h__

#include <boost/function.hpp>

void connect_in_new_thread(const char* server, unsigned short port, boost::function<void(int)> func);

#endif /* !__connect_h__ */

