/*
 * http_header.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __http_header_h__
#define __http_header_h__

#include "httpmuncher/config.h"

#include <map>
#include <string>
#ifndef OLDBOOST
#include <boost/algorithm/string.hpp>
#endif

#include "httpmuncher/util/logging.h"

#ifndef OLDBOOST
// see:
// stackoverflow.com/questions/1801892/making-mapfind-operation-case-insensitive
struct ciLessBoost : std::binary_function<std::string, std::string, bool>
{
	bool operator() (const std::string & s1, const std::string & s2) const {
		return boost::lexicographical_compare(s1, s2, boost::is_iless());
	}
};
#endif

class HttpHeader : public Logging {

	public:
#ifndef OLDBOOST
		typedef std::map<std::string, std::string, ciLessBoost> Map;
#else
		typedef std::map<std::string, std::string> Map;
#endif

		HttpHeader() { }

		HttpHeader( const std::string& raw_string );

		HttpHeader( const HttpHeader& other );

		virtual ~HttpHeader();

		virtual void set_initial_line( const std::string& value );

		virtual std::string get_initial_line() const;

		virtual void set( const std::string& key, const std::string& value );

		virtual std::string get( const std::string& key ) const;

		virtual std::string as_socket_data() const;

#ifdef LOGGING
		virtual std::string stringify_object() const;
#endif

	protected:
		Map header_map;

		std::string initial_line;

};

#endif /* !__http_header_h__ */

