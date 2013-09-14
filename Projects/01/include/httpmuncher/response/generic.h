/*
 * generic.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __generic_h__
#define __generic_h__

#include <map>
#include <boost/assign/list_of.hpp>

std::map<unsigned int, const char*> generic_response = boost::assign::map_list_of
(404, "HTTP/1.0 404 Not Found\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: 90\r\n\r\n<html><head><title>404 Not Found</title></head><body><h1>404 Not Found</h1></body></html>\r\n");

#endif /* !__generic_h__ */

