/*
 * sig_handle.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __sig_handle_h__
#define __sig_handle_h__

#include "httpmuncher/config.h"

#include <signal.h>

int handle_sigint(void (*func)(int)) {
	 struct sigaction action;

	 action.sa_handler = func;

	 return sigaction(SIGINT,&action,NULL);
}

#endif /* !__sig_handle_h__ */

