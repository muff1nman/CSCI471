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

// TODO wrap all this in a namespace

typedef std::map< const std::string, const std::string > MimeMap;

static const MimeMap EXT = boost::assign::map_list_of
(".txt", "text/text")
(".html", "text/html")
(".jpg", "image/jpeg")
;

static const std::string NO_VALUE("UNKNOWN");
static const std::string DEFAULT("text/text");

static const std::string& mime_type( const std::string& ext ) {
    MimeMap::const_iterator found = EXT.find(ext);
    if( found != EXT.end() ) {
        return found->second;
    } else {
        return DEFAULT;
    }
}

#endif /* !__extension_h__ */

