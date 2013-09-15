/*
 * extension.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __extension_h__
#define __extension_h__


#include <map>
#include <string>
#include <boost/assign/list_of.hpp>

static const std::map< const std::string, const std::string > EXT_MAP = boost::assign::map_list_of
(".txt", "text/text")
(".html", "text/html")
(".jpg", "image/jpeg")
;

// TODO do something meaningful if we dont find an ext
static const std::string& mime_type( const std::string& ext ) {
	return EXT_MAP.at(ext);
}

#endif /* !__extension_h__ */

