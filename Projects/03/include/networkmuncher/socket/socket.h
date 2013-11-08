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
		typedef boost::function<void(int)> SocketFunction;

		Socket( int socket_type, Port port);

		// TODO only for TCP socket
		//void listen(Port port);

		/** 
		 * Accept a connection and run the given socket function with the opened
		 * socket file descriptor
		 */
		void accept( SocketFunction f);

		/**
		 * connects and runs the given socket function with the created socket file
		 * descriptor
		 */
		void connect(const char* server, Port dest_port, SocketFunction f);

		void set_timeout(size_t usec, size_t sec);

		// TODO not implemented yet
		//void handle_c( int sig );
		
		/**
		 * Returns the internal socket fd.  It is okay to use this to close the
		 * socket. // TODO change it so that closing the socket is done in
		 * destructor
		 */
		int get_socket() {
			return socket_fd;
		}

	private:
		int socket_fd;
		int socket_type;
		int port;


};

#endif /* !__socket_h__ */

