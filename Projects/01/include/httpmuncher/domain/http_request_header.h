/*
 * http_request_header.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __http_request_header_h__
#define __http_request_header_h__

#include "httpmuncher/domain/http_header.h"

class HttpRequestHeader : public HttpHeader{

	public:
		HttpRequestHeader() { }

		HttpRequestHeader( const std::string& raw_string );

		HttpRequestHeader( const HttpRequestHeader& other );

		virtual ~HttpRequestHeader();

		virtual void set_initial_line( const std::string& value );

		virtual std::string get_http_version() const;

		virtual void set_http_version( const std::string& version );

		virtual std::string get_action() const;

		virtual void set_action( const std::string& action );

		virtual std::string get_path() const;

		virtual void set_path( const std::string& path );

#ifdef LOGGING
		virtual std::string stringify_object() const;
#endif

	protected:
		std::string path, action;
		std::string http_version;
};

#endif /* !__http_request_header_h__ */

