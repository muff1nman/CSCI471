/*
 * socket.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "networkmuncher/socket/socket.h"
#include "networkmuncher/util/logging.h"

#include "assist.h"
#include "socket_config.h"
#include "messages.h"
#include "socket_helper.h"

#include <string.h>
#include <boost/thread.hpp>
#include <boost/bind.hpp>


Socket::SocketFunction convert_to_socket_function( Socket::ConsumerPtr c ) {
	return boost::bind(&socket_thread_runner, _1, c);
}

Socket::SocketFunction convert_to_socket_function( Socket::ConsumerProvider cp ) {
	return convert_to_socket_function(cp());
}

void Socket::accept( SocketFunction f) {
	f(this);
}

void Socket::accept( ConsumerProvider cp, bool discarded) {
	accept(convert_to_socket_function(cp));
}

void Socket::accept( ConsumerPtr c ) {
	accept(convert_to_socket_function(c));
}

void Socket::connect(const struct sockaddr* addr, socklen_t len, SocketFunction f) {
	int connect_result = connect_to_socket( this->socket_fd, addr, len );
	if( connect_result < SUCCESS ) {
#ifdef LOGGING
		LOG(FATAL) << ERROR_CONNECT << ": " << strerror(errno);
#else
		perror(ERROR_CONNECT);
		exit(1);
#endif
	} else {
#ifdef LOGGING
		LOG(INFO) << "Connected to socket";
#endif
		f(this);
	}
}

void Socket::connect(const struct sockaddr* addr, socklen_t len, ConsumerProvider cp, bool discarded) {
	SocketFunction f = convert_to_socket_function(cp);
	connect( addr, len, f);
}

void Socket::connect(const struct sockaddr* addr, socklen_t len, ConsumerPtr c) {
	SocketFunction f = convert_to_socket_function(c);
	connect( addr, len, f);
}

void Socket::connect(const char* server, Port dest_port, SocketFunction f) {
	struct sockaddr_in address_info;
 	int convert_result = convert_server_info(server, dest_port, address_info);
	if( convert_result < SUCCESS ) {
		exit(1);
	} else {
		connect( (sockaddr*) &address_info, sizeof(address_info), f);
	}
}

void Socket::connect(const char* server, Port dest_port, ConsumerProvider cp, bool discarded) {
	connect( server, dest_port, convert_to_socket_function(cp));
}

void Socket::connect(const char* server, Port dest_port, ConsumerPtr c ) {
	connect( server, dest_port, convert_to_socket_function(c));
}

void Socket::set_timeout(size_t usec, size_t sec) {
	int timeout_result = set_timeout_internal( this->socket_fd, usec, sec);
	if( timeout_result < SUCCESS ) {
#ifdef LOGGING
		LOG(FATAL) << ERROR_TIMEOUT << ": " << strerror(errno);
#else
		perror(ERROR_TIMEOUT);
		exit(1);
#endif
	}

}

void Socket::open() {
	this->socket_fd = open_socket(socket_type, socket_protocol);
	if( this->socket_fd <  SUCCESS ) {
#ifdef LOGGING
		LOG(FATAL) << ERROR_CREATE_SOCKET << ": " << strerror(errno);
#else
		perror(ERROR_CREATE_SOCKET);
		exit(1);
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
		LOG(FATAL) << ERROR_BIND_SOCKET << ": " << strerror(errno);
#else
		perror(ERROR_BIND_SOCKET);
		exit(1);
#endif
	}
#ifdef LOGGING
	else {
		LOG(INFO) << "Bound socket";
	}
#endif

}

BytesContainer Socket::recv() {
	return all_data(socket_fd);
}

BytesContainer Socket::recv_from(sockaddr_in& remote_info, socklen_t& remote_info_size) {
	return all_data(socket_fd, remote_info, remote_info_size);
}

BytesContainer Socket::recv_from(sockaddr_in& remote_info, socklen_t& remote_info_size, size_t buf_size ) {
	return all_data(socket_fd, buf_size, remote_info, remote_info_size);
}

int Socket::send(const BytesContainer& to_send) {
	return send_data(socket_fd, to_send);
}

void Socket::close() {
	close_socket(this->socket_fd);
}

Socket::~Socket() { 
	close();
}

Socket::Socket( int socket_type, int protocol ) : socket_type(socket_type), socket_protocol(protocol) {
	open();
}

Socket::Socket( int socket_type, int protocol, Port port) : socket_type(socket_type), socket_protocol(protocol), port(port) {
	open();
	bind(port);
}




