/*
 * socket.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __socket_h__
#define __socket_h__

/**
 * if you wish to shutdown the accept action, close this file descriptor
 */
static int global_fd = 0;

/**
 * Blocking function that spins of threads for each new request coming in on the
 * given port
 */
void accept_in_new_threads(unsigned short port);

#endif /* !__socket_h__ */

