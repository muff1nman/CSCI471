/*
 * socket.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __socket_h__
#define __socket_h__


#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// For htons and htonl
#include <arpa/inet.h>

#include "httpmuncher/socket/consumer.h"
#include "httpmuncher/config.h"
#include "httpmuncher/util/messages.h"

#ifdef LOGGING
#include <glog/logging.h>
#endif


/**
 * Opens a socket to listen on returning the socket fd
 */
int open_listening_socket() {
#ifdef DEBUG
#ifdef LOGGING
	LOG(INFO) << "AF_INET is: " << AF_INET;
	LOG(INFO) << "SOCK_STREAM is: " << SOCK_STREAM;
#endif
#endif
	return socket(AF_INET, SOCK_STREAM, 0);
}

/**
 * Binds to a socket to a given port
 */
int bind_listening_socket_to_port(int socket_fd, unsigned short port_number) {
	struct sockaddr_in bind_opts;

	// clear out the structure just in case
	memset(&bind_opts, 0, sizeof(bind_opts));

	bind_opts.sin_family = AF_INET;
	bind_opts.sin_addr.s_addr = htonl(INADDR_ANY);
	bind_opts.sin_port = htons(port_number);

	return bind(socket_fd, (struct sockaddr*) &bind_opts, sizeof(bind_opts));
}

/**
 * Creates a listening socket and binds it to the given port number.  Returns
 * the listening socket file descriptor
 */
int create_listening_tcp_port( unsigned short port_number ) {
	int listening_fd = open_listening_socket();
	if( listening_fd != SUCCESS ) {
#ifdef LOGGING
		LOG(FATAL) << ERROR_LISTENING_SOCKET << ": " << listening_fd << " [" << strerror(listening_fd) << "]";
#else
		perror(ERROR_LISTENING_SOCKET);
#endif
		return listening_fd;
	}

	int bind_status = bind_listening_socket_to_port( listening_fd, port_number );
	if( bind_status != SUCCESS ) {
#ifdef LOGGING
		LOG(FATAL) << ERROR_BIND_SOCKET;
#else
		perror(ERROR_BIND_SOCKET);
#endif
		return bind_status; // we really just need a -1 value here
	}

	int listen_status = listen( listening_fd, BACKLOG );
	if( listen_status != SUCCESS ) {
#ifdef LOGGING
		LOG(FATAL) << ERROR_LISTEN;
#else
		perror(ERROR_LISTEN);
#endif
		return listen_status; // we really just need a -1 value here
	}

	return listening_fd;
}



void accept_in_new_threads() {
	int connection_fd;
	int listen_fd = create_listening_tcp_port( LISTEN_PORT );
	// we may assume listen_fd has already been checked...
	if ( listen_fd != SUCCESS ) {
		perror("error passed through create_listening_tcp_port...");
	}

	while(true) {
		LOG(INFO) << "Waiting on incoming requests";
		connection_fd = accept(listen_fd, NULL ,NULL);
		if( connection_fd != SUCCESS ) {
#ifdef LOGGING
			LOG(ERROR) << "Could not accept incoming request.. ignoring";
#endif
		} else {
#ifdef LOGGING
			LOG(INFO) << "Accepted incoming request";
#endif
			Consumer c(connection_fd);
			c();
		}
	}
}

#endif /* !__socket_h__ */

