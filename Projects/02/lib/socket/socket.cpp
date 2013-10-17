/*
 * socket.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dnsmuncher/socket/socket.h"
#include "dnsmuncher/util/logging.h"
#include "assist.h"
#include "socket_config.h"
#include "messages.h"

#include <netinet/ip.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

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
int open_socket(int type) {
	return socket(AF_INET, type, 0);
}

/**
 * Connects to a socket
 */
int connect_to_socket(int fd, const char* server, unsigned short port) {


#ifdef LOGGING
	LOG(INFO) << "Opened socket: [" << fd << "]";
#endif

	struct sockaddr_in address_info;

	memset( &address_info, 0, sizeof(address_info) );

	address_info.sin_family = AF_INET;
	address_info.sin_port = htons(port);
	int assign_addr_sucess = inet_aton( server, &(address_info.sin_addr) );
	if( assign_addr_sucess < SUCCESS ) {
		do_error( ERROR_IP_ADDR_CONVERT );
		return assign_addr_sucess;
	}

	int result = connect( fd, (struct sockaddr*) &address_info, sizeof(address_info));
	if (result != 0 ) {
		do_error( ERROR_CONNECT );
		return -1;
	}

	return fd;
}

void Socket::handle_c( int sig ) {
	int close_status = close(this->socket_fd);
	if(close_status < 0 ) {
#ifdef LOGGING
		LOG(ERROR) << "Could not close listening socket";
#endif
	} else {
#ifdef LOGGING
		LOG(INFO) << "Closed listening socket";
#endif
	}
}

void Socket::accept( SocketFunction f) {
	f(this->socket_fd);
}

void Socket::connect(const char* server, Port dest_port, SocketFunction f) {
	int connect_status = connect_to_socket( this->socket_fd, server, this->port);
	if( connect_status < SUCCESS ) {
#ifdef LOGGING
		LOG(ERROR) << ERROR_CONNECT << ": " << strerror(errno);
#else
		perror(ERROR_CONNECT);
#endif
	}

	boost::function<void()> bound_func = boost::bind(f, this->socket_fd);
	boost::thread t(bound_func);
}

Socket::Socket( int socket_type, Port port) : socket_type(socket_type), port(port) {
	this->socket_fd = open_socket(socket_type);
	if( this->socket_fd <  SUCCESS ) {
#ifdef LOGGING
		LOG(ERROR) << ERROR_CREATE_SOCKET << ": " << strerror(errno);
#else
		perror(ERROR_CREATE_SOCKET);
#endif
	}
	int bind_result = bind_listening_socket_to_port( this->socket_fd, port );
#ifdef LOGGING
	LOG(ERROR) << ERROR_BIND_SOCKET << ": " << strerror(errno);
#else
	perror(ERROR_BIND_SOCKET);
#endif
	
}




