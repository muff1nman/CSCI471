/*
 * status.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __status_h__
#define __status_h__

#include <map>
#include <string>
#include <boost/assign/list_of.hpp>

namespace HTTP {

	static const unsigned int CONTINUE = 200;
	static const unsigned int NOT_FOUND = 404;

	static const std::map< const unsigned int, const std::string > _MESSAGE = boost::assign::map_list_of
		( CONTINUE  , "Continue"  )
		( NOT_FOUND , "Not Found" );

	static const std::string& MESSAGE( unsigned int code ) {
		return _MESSAGE.at(code);
	}

	static const std::map<unsigned int, const char*> generic_response = boost::assign::map_list_of
		(404, "HTTP/1.0 404 Not Found\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: 90\r\n\r\n<html><head><title>404 Not Found</title></head><body><h1>404 Not Found</h1></body></html>\r\n");

	static const std::string debug_404_html = "<html><head><title>404 Not Found</title></head><body><h1>404 Not Found</h1></body></html>\r\n";

}

#endif /* !__status_h__ */

