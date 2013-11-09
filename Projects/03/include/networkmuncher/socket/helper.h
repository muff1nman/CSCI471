/*
 * helper.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __helper_h__
#define __helper_h__

#include "networkmuncher/util/logging.h"
#include "networkmuncher/util/byte/byte.h"
#include "networkmuncher/util/byte/print.h"
#include "networkmuncher/actors/consumer.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <boost/shared_ptr.hpp>
#include <cstdlib>

const char* const ALLOCATE_ERROR = "Could not allocate buffer space";

/*
 * Runs a consumer and deletes it after completion.
 *
 * This is mainly a helper function that is meant to be passed into
 * Socket#accept or Socket#connect
 */
inline void socket_thread_runner(int fd, boost::shared_ptr<Consumer> c) {
	c->run(fd);
#ifdef LOGGING
	LOG(INFO) << "Thread finalizing";
#endif

	// release the Consumer 
#ifdef LOGGING
	LOG(INFO) << "Releasing resources";
#endif
	c.reset();

#ifdef LOGGING
	LOG(INFO) << "Thread released";
#endif
}

inline bool check_allocated( void* data ) {
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

inline BytesContainer all_data( int socket_fd, size_t buf_size, sockaddr_in& remote_info, socklen_t& remote_info_size ) {
#ifdef LOGGING
	LOG(INFO) << "Buffer size set to [" << buf_size << "]";
#endif
	BytesContainer empty;

	Byte* data = (Byte*) malloc(buf_size); 
	if( !check_allocated(data) ) {
		return empty;
	}

	size_t bytes_read = 0;

	while(true) {
#ifdef LOGGING
		LOG(INFO) << "Reading from socket...";
#endif
		int read_status = recvfrom(socket_fd, data+bytes_read, buf_size - 1, 0, (sockaddr*) &remote_info, &remote_info_size );

		if( read_status > 0 ) {
			bytes_read += read_status;
			if( (unsigned) read_status < buf_size ) {
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
				data = (Byte*) realloc(data, bytes_read + 1 + buf_size);
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
	
	BytesContainer packaged_data( data, data + bytes_read);
	free(data);
	return packaged_data;
}

inline size_t guess_buffer_size(int socket_fd) {
	// // Maximum packet size as dictated by kernel
	//socklen_t optlen;
	//int optval;
	//getsockopt(socket_fd, SOL_SOCKET, SO_RCVBUF, (int *)&optval, &optlen);
	//return optval;
	
	// maximum udp packet size
	return 65536;
}

inline BytesContainer all_data( int socket_fd, sockaddr_in& remote_info, socklen_t& remote_info_size ) {
	return all_data( socket_fd, guess_buffer_size(socket_fd), remote_info, remote_info_size);
}

inline BytesContainer all_data( int socket_fd ) {
	socklen_t discard_len;
	sockaddr_in discard;

	return all_data( socket_fd, guess_buffer_size(socket_fd), discard, discard_len);
}
#endif /* !__helper_h__ */

