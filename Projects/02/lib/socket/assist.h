/*
 * assist.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __assist_h__
#define __assist_h__

#include "dnsmuncher/config.h"

#ifdef LOGGING
#include <glog/logging.h>
#else
#include <stdio.h>
#endif

void do_error(const char* msg) {
#ifdef LOGGING
	LOG(ERROR) << msg;
#else
	perror(msg);
#endif
}


#endif /* !__assist_h__ */

