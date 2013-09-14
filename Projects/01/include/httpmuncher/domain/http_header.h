/*
 * http_header.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __http_header_h__
#define __http_header_h__

#include <map>
#include <string>
#include <boost/algorithm/string.hpp>

#include "httpmuncher/util/logging.h"

// see:
// stackoverflow.com/questions/1801892/making-mapfind-operation-case-insensitive
struct ciLessBoost : std::binary_function<std::string, std::string, bool>
{
	bool operator() (const std::string & s1, const std::string & s2) const {
		return boost::lexicographical_compare(s1, s2, boost::is_iless());
	}
};

class HttpHeader : public Logging {

	public:

		HttpHeader() { }

		HttpHeader( const std::string& raw_string );

		HttpHeader( const HttpHeader& other );

		~HttpHeader();

		void set_initial_line( const char* value );

		const char* get_initial_line() const;

		void set( const char* key, const char* value );

		const char* get( const char* key ) const;

		virtual std::string stringify_object() const;

	protected:
		std::map<std::string, std::string, ciLessBoost> header_map;
		std::string initial_line;

};

#endif /* !__http_header_h__ */

