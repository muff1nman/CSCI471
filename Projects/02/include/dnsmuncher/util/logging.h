/*
 * logging.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __logging_h__
#define __logging_h__

#include "dnsmuncher/config.h"

#ifdef LOGGING
#include <string>
#include <boost/lexical_cast.hpp>
#include <glog/logging.h>
#endif

class Logging {

#ifdef LOGGING
	public:
		virtual std::string to_string() const { return std::string(nested_start) + stringify_object() + std::string(nested_finish); }
		virtual std::string stringify_object() const { return std::string("UNKNOWN"); }
#endif
	protected:
		virtual ~Logging() { }

};

#endif /* !__logging_h__ */

