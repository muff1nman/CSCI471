/*
 * http_request_header.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "httpmuncher/domain/http_request_header.h"

#ifndef OLDBOOST
#include <boost/spirit/include/classic.hpp>
#else
#include <boost/spirit.hpp>
#endif

#ifndef OLDBOOST
namespace bsp = boost::spirit::classic;
#else
namespace bsp = boost::spirit;
#endif

HttpRequestHeader::HttpRequestHeader( const std::string& raw_string ) : HttpHeader(raw_string) {
	this->set_initial_line( this->initial_line );
}

HttpRequestHeader::HttpRequestHeader( const HttpRequestHeader& other ) : HttpHeader(other) {
	this->path = other.path;
	this->action = other.action;
	this->http_version = other.http_version;
}

HttpRequestHeader::~HttpRequestHeader() {
	// noop	
}

void HttpRequestHeader::set_initial_line( const std::string& value ) {
	HttpHeader::set_initial_line( value );
	// TODO ensure these get set? // double checks in getters?
	//this->action = "unknown";
	//this->path = "unknown";
	//this->http_version = 0.0;
	bsp::parse( value.c_str(),
			(bsp::chseq_p("GET")[bsp::assign_a(this->action)] >> bsp::blank_p >> (*(bsp::anychar_p - bsp::space_p))[bsp::assign_a(this->path)] >> bsp::blank_p >> bsp::str_p("HTTP/") >> (bsp::str_p("1.1") | bsp::str_p("1.0"))[bsp::assign_a(this->http_version)])
			);
}

std::string HttpRequestHeader::get_http_version() const {
	return this->http_version;
}

void HttpRequestHeader::set_http_version( const std::string& version ) {
	this->http_version = version;
}

std::string HttpRequestHeader::get_action() const {
	return this->action;
}

void HttpRequestHeader::set_action( const std::string& action ) {
	this->action = action;
}

std::string HttpRequestHeader::get_path() const {
	return this->path;
}

void HttpRequestHeader::set_path( const std::string& path ) {
	this->path = path;
}

#ifdef LOGGING
std::string HttpRequestHeader::stringify_object() const {
	std::string info = HttpHeader::stringify_object();
	info += "path: " + this->path + list_sep;
	info += "action: " + this->action + list_sep;
	info += std::string("version: ") + boost::lexical_cast<std::string>(this->http_version) + sep;
	return info;
}
#endif


