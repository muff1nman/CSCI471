/*
 * socket.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __socket_h__
#define __socket_h__

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

#include "httpmuncher/socket/echo_consumer.h"
#include "httpmuncher/config.h"

#ifdef LOGGING
#include <glog/logging.h>
#endif

#ifdef DEBUG
#include <iostream>
#endif

static int global_fd = 0;

/**
 * Opens a socket to listen on returning the socket fd
 */
int open_listening_socket();

/**
 * Binds to a socket to a given port
 */
int bind_listening_socket_to_port(int socket_fd, unsigned short port_number);

/**
 * Creates a listening socket and binds it to the given port number.  Returns
 * the listening socket file descriptor
 */
int create_listening_tcp_port( unsigned short port_number );

void handle_c( int sig );

// Runs a consumer and deletes it after completion.
void thread_runner(Consumer* c);

void accept_in_new_threads();

#endif /* !__socket_h__ */

