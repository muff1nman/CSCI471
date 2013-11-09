/*
 * socket.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __socket_h__
#define __socket_h__

#include "networkmuncher/actors/consumer.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

/**
 * Because Im tired of having to deal with sockets
 */
class Socket {
	public:
		typedef unsigned short Port;

		/**
		 * Calls the given socket function with the underlying socket file
		 * descriptor passed in.
		 */
		typedef boost::function<void(int)> SocketFunction;

		/**
		 * Calls this function to retrieve a Consumer and then uses the returned
		 * Consumer's #run function as a SocketFunction
		 */
		typedef boost::function<boost::shared_ptr<Consumer>()> ConsumerProvider;

		/*
		 * Opens a socket and binds it to the given port
		 */
		Socket( int socket_type, Port port);

		/*
		 * Only opens up the socket
		 */
		Socket( int socket_type );

		// TODO only for TCP socket
		//void listen(Port port);

		/** 
		 * Accept a connection and run the given socket function with the opened
		 * socket file descriptor.  Only works for a bound socket
		 */
		void accept( SocketFunction f);

		/*
		 * Converts ConsumerProvider to a SocketFunction and then calls accept on
		 * the SocketFunction. discarded is just to differeniate between overloaded
		 * functions
		 */
		void accept( ConsumerProvider cp, bool discarded );

		/**
		 * connects and runs the given socket function with the created socket file
		 * descriptor
		 */
		void connect(const char* server, Port dest_port, SocketFunction f);

		/*
		 * Converts ConsumerProvider to a SocketFunction and then calls connect on
		 * the SocketFunction. discarded is just to differeniate between overloaded
		 * functions
		 */
		void connect(const char* server, Port dest_port, ConsumerProvider cp, bool discarded);

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

		~Socket();

	private:
		int socket_fd;
		int socket_type;
		int port;

		void open();
		void bind(Port port);

		/**
		 * Attempts to close this socket.  This is automatically called by the
		 * destructor.  
		 */
		void close();


};

#endif /* !__socket_h__ */

