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
		//typedef void (*SocketFunction)(int);
		typedef boost::function<void(int)> SocketFunction;
		Socket( int socket_type, Port port);

		// TODO only for TCP socket
		//void listen(Port port);
	
		// TODO accept in thread?
		void accept( SocketFunction f);

		void connect(const char* server, Port dest_port, SocketFunction f);

		void set_timeout(size_t usec, size_t sec);

		// TODO not implemented yet
		//void handle_c( int sig );
		
		int get_socket() {
			return socket_fd;
		}

	private:
		int socket_fd;
		int socket_type;
		int port;


};

#endif /* !__socket_h__ */

