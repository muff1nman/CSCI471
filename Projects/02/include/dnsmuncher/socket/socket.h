/*
 * socket.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __socket_h__
#define __socket_h__

#include <sys/socket.h>
#include <boost/function.hpp>

/**
 * Because Im tired of having to deal with sockets
 */
class Socket {
	public:
		typedef unsigned short Port;
		typedef void (*SocketFunction)(int);
		Socket( int socket_type, Port port);

		// TODO only for TCP socket
		//void listen(Port port);
		
		void accept( SocketFunction f);

		void connect(const char* server, Port dest_port, SocketFunction f);


	private:
		int socket_fd;
		int socket_type;

		int open_connect_socket() {
			return socket(AF_INET, socket_type, 0);
		}

		void bind_to_port( Port port );

};

#endif /* !__socket_h__ */

