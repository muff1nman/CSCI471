/*
 * http_response_header.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __http_response_header_h__
#define __http_response_header_h__

#include "httpmuncher/domain/http_header.h"
#include "httpmuncher/response/status.h"

class HttpResponseHeader : public HttpHeader{
	public:

		HttpResponseHeader(unsigned int status = HTTP::NOT_FOUND, const std::string& version = "1.0") :
			HttpHeader(), status(status), http_version(version) { this->update_initial(); }

		HttpResponseHeader( const HttpResponseHeader& other );

		virtual ~HttpResponseHeader();

		virtual void set_initial_line( const std::string& value );

		virtual std::string get_http_version() const;

		virtual void set_http_version( const std::string& version );

		virtual unsigned int get_status() const;

		virtual void set_status( unsigned int status );

#ifdef LOGGING
		virtual std::string stringify_object() const;
#endif

	protected:
		unsigned int status;
		std::string http_version;

	private:
		void update_initial();

};

#endif /* !__http_response_header_h__ */

