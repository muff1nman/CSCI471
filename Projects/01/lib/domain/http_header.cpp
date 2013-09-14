/*
 * http_header.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include <boost/spirit.hpp>

#include "httpmuncher/domain/http_header.h"
#ifdef DEBUG
#include <iostream>
#endif

namespace bsp = boost::spirit;

HttpHeader::HttpHeader( const std::string& raw_string ) {

	bool parsed_successfully = bsp::parse( raw_string.c_str(),(*( bsp::anychar_p  - bsp::eol_parser()))[bsp::assign_a(this->initial_line)], bsp::space_p).full;

#ifdef DEBUG
    std::cout << "header: " << this->initial_line << std::endl;
#endif

#ifdef LOGGING
	LOG(INFO) << "parsed successfully? " << parsed_successfully;
	LOG(INFO) << "initial line is: " << this->initial_line;
#endif
}

HttpHeader::HttpHeader( const HttpHeader& other ) { }

void HttpHeader::set_initial_line( const char* value ) {

}

HttpHeader::~HttpHeader() {

}

const char* HttpHeader::get_initial_line() const {

}

void HttpHeader::set( const char* key, const char* value ) {

}

const char* HttpHeader::get( const char* key ) const {

}

std::string HttpHeader::stringify_object() const {
	std::string info("");
	info += "initial line: " + this->initial_line;
	return info;
}

