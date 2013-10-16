/*
 * socket.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dnsmuncher/socket/socket.h"
#include "dnsmuncher/util/logging.h"

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

Socket::Socket( int socket_type, Port port) : socket_type(socket_type), port(port) {
	this->socket_fd = open_socket(socket_type);
}




