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
	HttpHeader h(split_away_raw_header( socket_fd ));
}

bool matches_newline( size_t index, const char* data, size_t size ) {
	if( index + 1 == size ) {
		return data[index] == '\n';
	} else if ( index + 1 < size ) {
		return data[index] == '\n' || (data[index] == '\r' && data[index + 1] == '\n');
	} else {
		return false;
	}
}

size_t characters_remaining( size_t index, size_t size ) {
	return size - index;
}

// not safe
bool matches_double_newline_chars( size_t index, const char* data ) {
	return data[index] == '\n' && data[index+1] == '\n';
}

bool matches_double_newline( size_t index, const char* data, size_t size ) {
	size_t left = characters_remaining( index, size );
	if ( left > 0 && left < 4 ) {
		// only check for two newlines
	} else {
		// check for two newlines or (two carriadge returns and two newlines)
	}
}

// returns the index of the occurance, otherwise returns -1
int search_for_double_newline( const char* data, size_t size_of_valid_data ) {
/*
 *  for( unsigned int i = 0; i< size_of_valid_data; ++i ) {
 *    if( matches_newline( 
 *#ifdef LOGGING
 *      LOG(INFO) << "Found double newline at: " << i;
 *#endif
 *      return i;
 *    }
 *  }
 *#ifdef LOGGING
 *  LOG(INFO) << "Did not find newline";
 *#endif
 *  return -1;
 */

	boost::match_results<const char*> result;
	static const boost::regex double_newlines("([\r]?\n){2}");
	if( boost::regex_search(data, data+size_of_valid_data, result, double_newlines) ) {
		int newlines_at = result.position();
#ifdef LOGGING
		LOG(INFO) << "Newlines at:" << newlines_at;
#endif
		return newlines_at;
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



