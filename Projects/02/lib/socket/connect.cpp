/*
 * connect.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dnsmuncher/config.h"
#include "dnsmuncher/socket/connect.h"
#include "socket_config.h"
#include "messages.h"
#include "assist.h"

#include <netinet/ip.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>

// threading
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#ifdef DEBUG
#include <iostream>
#endif

int open_connect_socket() {
	return socket(AF_INET, SOCK_DGRAM, 0);
}

int connect_to_socket(const char* server, unsigned short port) {
	int fd = open_connect_socket();

	if( fd <  SUCCESS ) {
		do_error(ERROR_CREATE_SOCKET);
		return fd;
	}

	struct sockaddr_in address_info;

	memset( &address_info, 0, sizeof(address_info) );

	address_info.sin_family = AF_INET;
	address_info.sin_port = htons(port);
	int assign_addr_sucess = inet_aton( server, &(address_info.sin_addr) );
	if( assign_addr_sucess < SUCCESS ) {
		do_error( ERROR_IP_ADDR_CONVERT );
		return assign_addr_sucess;
	}

	return connect( fd, (struct sockaddr*) &address_info, sizeof(address_info));
}

void connect_in_new_thread(const char* server, unsigned short port, boost::function<void(int)> func) {
	int connection_fd = connect_to_socket(server, port);
	if( connection_fd < SUCCESS ) {
		do_error( ERROR_CONNECT );
		return;
	}
	boost::function<void()> bound_func = boost::bind(func, connection_fd);
	boost::thread t(bound_func);
}


