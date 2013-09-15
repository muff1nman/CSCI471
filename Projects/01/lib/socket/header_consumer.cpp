/*
 * header_consumer.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "httpmuncher/socket/header_consumer.h"
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

void HeaderConsumer::run() {
	this->header = new HttpHeader(split_away_raw_header( socket_fd ));
}

HeaderConsumer::~HeaderConsumer() {
	delete this->header;
}

// returns the index of the occurance, otherwise returns -1
int search_for_double_newline( const char* data, size_t size_of_valid_data ) {
	boost::match_results<const char*> result;
	static const boost::regex double_newlines("([\r]?\n){2}");
	if( boost::regex_search(data, data+size_of_valid_data, result, double_newlines) ) {
		int newlines_at = result.position();
#ifdef LOGGING
		LOG(INFO) << "Newlines at:" << newlines_at << "size of match: " << result.length() << " text of match: " << result.str();
#endif
		return newlines_at + result.length();
	} else {
		return -1;	
	}
}

void add_to_string( std::string& data, const char* new_data, size_t size_of_new_data ) {
	data += std::string( new_data, size_of_new_data );
}

std::string HeaderConsumer::split_away_raw_header( int fd ) {
	char buffer[BUFSIZE];
	std::string header("");

	while(true) {
#ifdef LOGGING
		LOG(INFO) << "Reading from socket...";
#endif
		int read_status = read(fd, buffer, BUFSIZE - 1);

		if( read_status > 0 ) {
#ifdef LOGGING
			LOG(INFO) << "Read " << read_status << " bytes";
			for( size_t  i = 100; i < read_status; ++i ) {
				LOG(INFO) << "byte: " << buffer[i];
			}
#endif
			int index_of_newline = search_for_double_newline( buffer, read_status );
#ifdef LOGGING
			LOG(INFO) << "newline at: " << index_of_newline;
			LOG(INFO) << "character before: " << buffer[index_of_newline - 1];
#endif

			if (index_of_newline > 0 ) { // if there is a newline
				add_to_string( header, buffer, index_of_newline );
				// TODO push back fd?
#ifdef LOGGING
				LOG(INFO) << header;
				LOG(INFO) << "Found newline";
#endif
				break;
			} else { // no new line
#ifdef LOGGING
				LOG(INFO) << "Keep getting data...";
#endif
				add_to_string( header, buffer, read_status );
			}


			if ( read_status >= BUFSIZE - 1 ) {
#ifdef LOGGING
				LOG(INFO) << "Full buffer... more content coming?";
#endif

			} else { 
#ifdef LOGGING
				LOG(INFO) << "Content read from connection" << "\nSTART REQUEST\n" << buffer << "\nEND REQUEST";
#endif
				// TODO return empty string, because no valid header found?
				break;

			}
		} else if(read_status == 0 ) {
#ifdef LOGGING
			LOG(INFO) << "No more bytes";
#endif
			break; // natural end of stream?
		} else {
#ifdef LOGGING
			LOG(ERROR) << "read status: " << read_status;
#endif
			break;
		}
	}

	return header;
}



