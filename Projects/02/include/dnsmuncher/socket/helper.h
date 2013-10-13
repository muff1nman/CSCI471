/*
 * helper.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __helper_h__
#define __helper_h__

#include "dnsmuncher/util/logging.h"
#include "dnsmuncher/util/byte.h"
#include "dnsmuncher/util/byte_print.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <boost/shared_ptr.hpp>
#include <cstdlib>

const char* const ALLOCATE_ERROR = "Could not allocate buffer space";

void close_socket(int socket_fd) {
	int close_status = close(socket_fd);
	if( close_status < 0 ) {
#ifdef LOGGING
		// TODO put error code here
		LOG(ERROR) << "Could not close socket: ";
		// TODO do something better?
#endif
	}
#ifdef LOGGING
	else {
		LOG(INFO) << "Closed socket";
	}
#endif
}

bool check_allocated( void* data ) {
	if( data == NULL ) {
#ifdef LOGGING
		LOG(ERROR) << ALLOCATE_ERROR;
#else
		perror( ALLOCATE_ERROR );
#endif
		return false;
	}
	return true;
}

BytesContainer all_data( int socket_fd, size_t buf_size ) {
#ifdef LOGGING
	LOG(INFO) << "Buffer size set to [" << buf_size << "]";
#endif
	BytesContainer empty;
	empty.size = 0;

	Byte* data = (Byte*) malloc(buf_size); 
	if( !check_allocated(data) ) {
		return empty;
	}

	size_t bytes_read = 0;

	while(true) {
#ifdef LOGGING
		LOG(INFO) << "Reading from socket...";
#endif
		int read_status = read(socket_fd, data+bytes_read, buf_size );

		if( read_status > 0 ) {
			bytes_read += read_status;
			if( read_status < buf_size ) {
#ifdef LOGGING
				LOG(INFO) << "No more bytes";
				LOG(INFO) << std::endl << demaria_util::to_string(data, read_status, 4, 10 );
#endif
				break; // end of stream?
			} else {
				// more bytes?
#ifdef LOGGING
				LOG(INFO) << "Read " << read_status << " bytes from connection" << "\nSTART REQUEST\n" << data << "\nPOSSIBLE END REQUEST (more content in next buffer?)";
#endif

#ifdef LOGGING
				LOG(INFO) << "Allocating more space";
#endif
				data = (Byte*) realloc(data, bytes_read + buf_size);
				if( !check_allocated(data) ) {
					return empty;
				}
			}
		} else if(read_status == 0 ) {
#ifdef LOGGING
			LOG(WARNING) << "No bytes read";
#endif
			break; // natural end of stream?
		} else {
#ifdef LOGGING
			LOG(WARNING) << "read status: " << read_status;
#endif
			break;
		}
	}

	BytesContainer valid;
	valid.size = buf_size;
	// TODO really we should try to keep this close to the malloc and realloc
	// calls
	valid.data = Bytes( data, free );

	return valid;
}

size_t guess_buffer_size(int socket_fd) {
	// // Maximum packet size as dictated by kernel
	//socklen_t optlen;
	//int optval;
	//getsockopt(socket_fd, SOL_SOCKET, SO_RCVBUF, (int *)&optval, &optlen);
	//return optval;
	
	// maximum udp packet size
	return 65536;
}

BytesContainer all_data( int socket_fd ) {
	return all_data( socket_fd, guess_buffer_size(socket_fd) );
}

#endif /* !__helper_h__ */

