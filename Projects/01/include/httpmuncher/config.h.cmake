/*
 * config.h.cmake
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __config_h__
#define __config_h__

#cmakedefine DEBUG
#cmakedefine LOGGING

#define LOG_LEVEL @LOG_LEVEL@

// FOR logging stuffs
#define sep " "
#define list_sep ", "
#define nested_start "[ "
#define nested_finish  "]"

const int SUCCESS = 0;

#define BACKLOG 12

#define LISTEN_PORT 16318

#endif /* !__config_h__ */

