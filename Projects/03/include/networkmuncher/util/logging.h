/*
 * logging.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __logging_h__
#define __logging_h__

#include "networkmuncher/config.h"

#ifdef LOGGING
#include <boost/lexical_cast.hpp>
#include <glog/logging.h>
#endif
#include <string>
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

		virtual std::string to_string() const { return std::string(nested_start) + stringify_object() + std::string(nested_finish); }
		virtual std::string stringify_object() const { return std::string("UNKNOWN"); }
	protected:
		virtual ~Logging() { }

};

/**
 * Needs to be called before any logging can be done. This function is a no-op
 * if logging is not defined.
 */
void init_log(size_t log_level, const char* project_name);

#endif /* !__logging_h__ */

