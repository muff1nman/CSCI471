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
#include "networkmuncher/actors/socket_consumer.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <boost/shared_ptr.hpp>
#include <boost/optional.hpp>
#include <cstdlib>

const char* const ALLOCATE_ERROR = "Could not allocate buffer space";

/**
 * Binds to a socket to a given port
 */
int bind_listening_socket_to_port(int socket_fd, Socket::Port port_number) {
	struct sockaddr_in bind_opts;

	// clear out the structure just in case
	memset(&bind_opts, 0, sizeof(bind_opts));

	bind_opts.sin_family = AF_INET;
	bind_opts.sin_addr.s_addr = htonl(INADDR_ANY);
	bind_opts.sin_port = htons(port_number);

	return bind(socket_fd, (struct sockaddr*) &bind_opts, sizeof(bind_opts));
}

/**
 * Opens a socket and returns the file descriptor
 */
int open_socket(int type, int protocol) {
	return socket(AF_INET, type, protocol);
}

int set_timeout_internal(int socket_fd, size_t timeout_in_usec, size_t timeout_in_sec ) {
	struct timeval timeout;
	timeout.tv_sec = timeout_in_sec;
	timeout.tv_usec = timeout_in_usec;

	return setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
}

inline void close_socket(int socket_fd) {
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

int connect_to_socket( int fd, const struct sockaddr* address, socklen_t address_len ) {
	int result = connect( fd, address, address_len);
	if (result != 0 ) {
		do_error( ERROR_CONNECT );
		return -1;
	}

	return fd;
}

int convert_server_info( const char* server, unsigned short port, sockaddr_in& address_info ) {
	memset( &address_info, 0, sizeof(address_info) );

	address_info.sin_family = AF_INET;
	address_info.sin_port = htons(port);
	int assign_addr_sucess = inet_aton( server, &(address_info.sin_addr) );
	if( assign_addr_sucess < SUCCESS ) {
		do_error( ERROR_IP_ADDR_CONVERT );
		return -1;
	}
	return 0;

}

/**
 * Connects to a socket
 */
int connect_to_socket(int fd, const char* server, unsigned short port) {
	struct sockaddr_in address_info;
 	int convert_result = convert_server_info(server, port, address_info);
	if( convert_result < SUCCESS ) {
		return connect_to_socket( fd, (sockaddr*) &address_info, sizeof(address_info));
	} else {
		return -1;
	}
}


/*
 * Runs a consumer and deletes it after completion.
 *
 * This is mainly a helper function that is meant to be passed into
 * Socket#accept or Socket#connect
 */
inline void socket_thread_runner(Socket* socket, boost::shared_ptr<SocketConsumer> c) {
	c->run(socket);
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

inline boost::optional<BytesContainer> all_data( int socket_fd, size_t buf_size, sockaddr_in& remote_info, socklen_t& remote_info_size ) {
#ifdef LOGGING
	LOG(INFO) << "Buffer size set to [" << buf_size << "]";
#endif
	boost::optional<BytesContainer> optional_bytes;

	Byte* data = (Byte*) malloc(buf_size); 
	if( !check_allocated(data) ) {
		return optional_bytes;
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
					return optional_bytes;
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
	
	if(bytes_read > 0 ) {
		optional_bytes = BytesContainer( data, data + bytes_read);
	}
	free(data);
	return optional_bytes;
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

/*
 * Acts like the kernel call recvfrom and can be used on either a bound or
 * unbound socket
 */
inline boost::optional<BytesContainer> all_data( int socket_fd, sockaddr_in& remote_info, socklen_t& remote_info_size ) {
	return all_data( socket_fd, guess_buffer_size(socket_fd), remote_info, remote_info_size);
}

/*
 * Acts like the kernel call recv and should be used on a bound socket
 */
inline boost::optional<BytesContainer> all_data( int socket_fd ) {
	socklen_t discard_len;
	sockaddr_in discard;

	return all_data( socket_fd, guess_buffer_size(socket_fd), discard, discard_len);
}

inline int send_data( int socket_fd, const BytesContainer& to_send ) {
	int result = send(socket_fd, to_send.data(), to_send.size(), 0);
#ifdef LOGGING
	if( result < SUCCESS ) {
		LOG(WARNING) << "Could not write to socket: " << strerror(errno);
	} else {
		LOG(INFO) << "[" << result << "] bytes written";
	}
#endif
	return result;
}

#endif /* !__helper_h__ */

