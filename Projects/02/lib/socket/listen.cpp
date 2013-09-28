/*
 * listen.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dnsmuncher/socket/listen.h"
#include "dnsmuncher/util/messages.h"
#include "dnsmuncher/util/sig_handle.h"
#include "dnsmuncher/socket/consumer.h"
//#include "dnsmuncher/socket/echo_consumer.h"
#include "dnsmuncher/config.h"
#include "socket_config.h"

// Netowkring stuff
#include <sys/socket.h>
#include <netinet/in.h>
// For htons and htonl
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

// threading
#include <boost/thread.hpp>
#ifdef OLDBOOST
#include <boost/bind.hpp>
#endif

#ifdef LOGGING
#include <glog/logging.h>
#endif

#ifdef DEBUG
#include <iostream>
#endif

/**
 * Opens a socket to listen on returning the socket fd
 */
int open_listening_socket() {
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
	if( listening_fd < SUCCESS ) {
#ifdef LOGGING
		LOG(FATAL) << ERROR_LISTENING_SOCKET << ": " << listening_fd << " [" << strerror(errno) << "]";
#else
		perror(ERROR_LISTENING_SOCKET);
#endif
		return listening_fd;
	}

	int bind_status = bind_listening_socket_to_port( listening_fd, port_number );
	if( bind_status < SUCCESS ) {
#ifdef LOGGING
		LOG(FATAL) << ERROR_BIND_SOCKET;
#else
		perror(ERROR_BIND_SOCKET);
#endif
		return bind_status; // we really just need a -1 value here
	}

	int listen_status = listen( listening_fd, BACKLOG );
	if( listen_status < SUCCESS ) {
#ifdef LOGGING
		LOG(FATAL) << ERROR_LISTEN;
#else
		perror(ERROR_LISTEN);
#endif
		return listen_status; // we really just need a -1 value here
	}

	return listening_fd;
}

void handle_c( int sig ) {
	int close_status = close(global_fd);
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

void accept_in_new_threads(unsigned short port, boost::function<void(int)> func) {
	int connection_fd;
	int listen_fd = create_listening_tcp_port( port );
	// we may assume listen_fd has already been checked...
	if ( listen_fd < SUCCESS ) {
		perror("error passed through create_listening_tcp_port...");
	}

	// save the global handler
	global_fd = listen_fd;

	// create a sigint handler
	handle_sigint(handle_c);

	while(true) {
#ifdef LOGGING
		LOG(INFO) << "Waiting for incoming requests on port " << port;
#endif
		connection_fd = accept(listen_fd, NULL ,NULL);
		if( connection_fd < SUCCESS ) {
#ifdef LOGGING
			LOG(ERROR) << "Could not accept incoming request.. (quit)";
#endif
			break;
		} else {
#ifdef LOGGING
			LOG(INFO) << "Accepted incoming request";
#endif

			boost::thread t(boost::bind(func, connection_fd));
		}
	}
}
