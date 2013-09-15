/*
 * http_header.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "httpmuncher/config.h"

#ifndef OLDBOOST
#include <boost/spirit/include/classic.hpp>
#else
#include <boost/spirit.hpp>
#endif

#include "httpmuncher/domain/http_header.h"
#ifdef DEBUG
#include <iostream>
#endif

#ifndef OLDBOOST
namespace bsp = boost::spirit::classic;
#else
namespace bsp = boost::spirit;
#endif

struct save_to_map
{
	save_to_map(HttpHeader::Map* map,  std::string* first, std::string* second)
		: map(map), first(first), second(second) {}

	void
		operator()(const char* not_used, const char* not_used_two) const
		{
#ifdef LOGGING
			LOG(INFO) << "Saving key: " << *first << " with value: " << *second;
#endif
			(*map)[*first] = *second;
		}

	HttpHeader::Map* map;
	std::string* first;
	std::string* second;

};

HttpHeader::HttpHeader( const std::string& raw_string ) {

	std::string first;
	std::string second;
	std::string remaining;
	save_to_map maper(&this->header_map, &first, &second);

	bool parsed_successfully = bsp::parse( raw_string.c_str(),
			(*( bsp::anychar_p  - bsp::eol_p))[bsp::assign_a(this->initial_line)] >> bsp::eol_p >> 
			*(((*( bsp::anychar_p - bsp::ch_p(':')))[bsp::assign_a(first)] >> bsp::ch_p(':') >> bsp::space_p >> (*( bsp::anychar_p - bsp::eol_p))[bsp::assign_a(second)])[maper] >> bsp::eol_p) >> (bsp::eol_p)[bsp::assign_a(remaining)]
			).full;
#ifdef DEBUG
#ifdef LOGGING
	LOG(INFO) << "parsed successfully? " << parsed_successfully;
	LOG(INFO) << "remaining characters: " << remaining << " length: " << remaining.size();
	LOG(INFO) << std::string("HttpHeader: ") + this->to_string();
#else
    std::cout << "parsed initial line: [" << this->initial_line << "]"<< std::endl;
#endif
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
	info += std::string("initial line: [") + this->initial_line + "]";
	HttpHeader::Map::const_iterator iter = this->header_map.begin();
	for( ; iter != this->header_map.end(); ++iter ) {
		info += std::string("Key: [") + iter->first + "] value: [" + iter->second + "]" + list_sep;
	}
	return info;
}

