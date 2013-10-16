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
#include <cstdio>
#include <cstdlib>
#include <sstream>

#define sep " "
#define list_sep ", "
#define nested_start "[ "
#define nested_finish  "]"

class Logging {
	public:
		static void do_error(const char* msg) { 
#ifdef LOGGING
			LOG(FATAL) << msg;
#else
			perror(msg);
#endif
			exit(1);
		}

#ifdef LOGGING
		virtual std::string to_string() const { return std::string(nested_start) + stringify_object() + std::string(nested_finish); }
		virtual std::string stringify_object() const { return std::string("UNKNOWN"); }
	protected:
		virtual ~Logging() { }
#endif

};


#endif /* !__logging_h__ */

