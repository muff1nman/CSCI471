/*
 * http_response_header.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "httpmuncher/domain/http_response_header.h"
#include "httpmuncher/util/number.h"

HttpResponseHeader::HttpResponseHeader( const HttpResponseHeader& other ) : HttpHeader(other) {
	this->http_version = other.http_version;
	this->status = other.status;
	this->update_initial();
}

HttpResponseHeader::~HttpResponseHeader() {
	// noop
}


std::string internal_update_initial_line( unsigned int status, const std::string& version ) {
	return std::string("HTTP/") + version + std::string(" ") +
		NumberToString(status) + std::string(" ") +
		HTTP::MESSAGE(status); 
}

void HttpResponseHeader::update_initial() {
	this->initial_line = internal_update_initial_line( this->status, this->http_version );
}

void HttpResponseHeader::set_initial_line( const std::string& value ) {
	// TODO noop? bad..
}

std::string HttpResponseHeader::get_http_version() const {
	return this->http_version;
}

void HttpResponseHeader::set_http_version( const std::string& version ) {
	this->http_version = version;
	this->update_initial();
}

unsigned int HttpResponseHeader::get_status() const {
	return this->status;
}

void HttpResponseHeader::set_status( unsigned int status ) {
	this->status = status;
	this->update_initial();
}

#ifdef LOGGING
std::string HttpResponseHeader::stringify_object() const {
	std::string info = HttpHeader::stringify_object();
	info += "status: " + boost::lexical_cast<std::string>(this->status) + list_sep;
	info += "version: " + this->http_version + sep;
};
#endif

