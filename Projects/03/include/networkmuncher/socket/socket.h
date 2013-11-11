/*
 * socket.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __socket_h__
#define __socket_h__

#include "networkmuncher/util/byte/byte.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

class Consumer;

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
		typedef boost::function<void(Socket*)> SocketFunction;

		typedef boost::shared_ptr<Consumer> ConsumerPtr;
		/**
		 * Calls this function to retrieve a Consumer and then uses the returned
		 * Consumer's #run function as a SocketFunction
		 */
		typedef boost::function<ConsumerPtr()> ConsumerProvider;

		/*
		 * Opens a socket and binds it to the given port
		 */
		Socket( int socket_type, int socket_protocol, Port port);

		/*
		 * Only opens up the socket
		 */
		Socket( int socket_type, int socket_protocol);

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
		void accept( ConsumerPtr c );

		/**
		 * Similar to the first connect but provides a higher level abstraction of
		 * specifying the remote server to connect to
		 */
		void connect(const struct sockaddr* addr, socklen_t len, SocketFunction f);

		/*
		 * Converts ConsumerProvider to a SocketFunction and then calls connect on
		 * the SocketFunction. discarded is just to differeniate between overloaded
		 * functions
		 */
		void connect(const struct sockaddr* addr, socklen_t len, ConsumerProvider cp, bool discarded);
		void connect(const struct sockaddr* addr, socklen_t len, ConsumerPtr c);

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
		void connect(const char* server, Port dest_port, ConsumerPtr c );

		void set_timeout(size_t usec, size_t sec);

		// TODO not implemented yet
		//void handle_c( int sig );
		
		/**
		 * Returns all data currently available on the given socket.  Blocks if
		 * there is no data.  TODO Assumes that socket is bound 
		 */
		BytesContainer recv();

		/**
		 * Returns all data currently available on the given socket from the remote
		 * server. Blocks if there is no data.
		 */
		BytesContainer recv_from(sockaddr_in& remote_info, socklen_t& remote_info_size);

		/**
		 * Returns all data currently available on the given socket from the remote
		 * server. Blocks if there is no data. Use the given buffer size for
		 * intermediate reading of data (the buffer does not limit the bytes read,
		 * only dicates how many bytes are read at a time)
		 */
		BytesContainer recv_from(sockaddr_in& remote_info, socklen_t& remote_info_size, size_t buf_size );

		/**
		 * Sends the given data.  Assumes that the socket is already connected.
		 * The return result is the result of the send operation.
		 */
		int send(const BytesContainer& to_send);

		
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
		int socket_protocol;
		int port;

		void open();
		void bind(Port port);

		/**
		 * Attempts to close this socket.  This is automatically called by the
		 * destructor.  
		 */
		void close();

		// not to be used
		Socket(const Socket& other) { }

};

#endif /* !__socket_h__ */

