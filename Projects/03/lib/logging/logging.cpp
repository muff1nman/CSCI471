/*
 * logging.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "networkmuncher/util/logging.h"

#ifdef LOGGING
#include <glog/logging.h>
#endif

void init_log(size_t log_level, const char* project_name) {
#ifdef LOGGING
	google::InitGoogleLogging(project_name);
	FLAGS_minloglevel = log_level;
	FLAGS_alsologtostderr = 1;
	FLAGS_colorlogtostderr = 1;
#endif
}


