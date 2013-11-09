/*
 * socket.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "networkmuncher/socket/socket.h"
#include "networkmuncher/socket/helper.h"
#include "networkmuncher/util/logging.h"
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

void Socket::accept( SocketFunction f) {
	f(this->socket_fd);
}

void Socket::connect(const char* server, Port dest_port, SocketFunction f) {
	int connect_status = connect_to_socket( this->socket_fd, server, dest_port);
	if( connect_status < SUCCESS ) {
#ifdef LOGGING
		LOG(ERROR) << ERROR_CONNECT << ": " << strerror(errno);
#else
		perror(ERROR_CONNECT);
#endif
	}
#ifdef LOGGING
	else {
		LOG(INFO) << "Connected to socket";
	}
#endif

	boost::function<void()> bound_func = boost::bind(f, this->socket_fd);
	//boost::thread t(bound_func);
	bound_func();
}

void Socket::set_timeout(size_t usec, size_t sec) {
	int timeout_result = set_timeout_internal( this->socket_fd, usec, sec);
	if( timeout_result < SUCCESS ) {
#ifdef LOGGING
		LOG(ERROR) << ERROR_TIMEOUT << ": " << strerror(errno);
#else
		perror(ERROR_TIMEOUT);
#endif
	}

}

void Socket::open() {
	this->socket_fd = open_socket(socket_type);
	if( this->socket_fd <  SUCCESS ) {
#ifdef LOGGING
		LOG(ERROR) << ERROR_CREATE_SOCKET << ": " << strerror(errno);
#else
		perror(ERROR_CREATE_SOCKET);
#endif
	}
#ifdef LOGGING
	LOG(INFO) << "Opened socket";
#endif

}

void Socket::bind(Port port) {
	int bind_result = bind_listening_socket_to_port( this->socket_fd, port );
	if(bind_result < SUCCESS) {
#ifdef LOGGING
		LOG(ERROR) << ERROR_BIND_SOCKET << ": " << strerror(errno);
#else
		perror(ERROR_BIND_SOCKET);
#endif
	}
#ifdef LOGGING
	else {
		LOG(INFO) << "Bound socket";
	}
#endif

}

void Socket::close() {
	close_socket(this->socket_fd);
}

Socket::~Socket() { 
	close();
}

Socket::Socket( int socket_type ) : socket_type(socket_type) {
	open();
}

Socket::Socket( int socket_type, Port port) : socket_type(socket_type), port(port) {
	open();
	bind(port);
}




