/*
 * http_header.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "httpmuncher/domain/http_header.h"

HttpHeader::HttpHeader( const char* raw_string ) { }

HttpHeader::HttpHeader( const HttpHeader& other ) { }

void HttpHeader::set_initial_line( const char* value );

const char* HttpHeader::get_initial_line() const;

void HttpHeader::set( const char* key, const char* value );

const char* HttpHeader::get( const char* key ) const;
