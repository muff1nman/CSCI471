/*
 * file_ops.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __file_ops_h__
#define __file_ops_h__

#include "dnsmuncher/util/byte/byte.h"
#ifdef LOGGING
#include <glog/logging.h>
#endif

#include <fstream>

// See http://codereview.stackexchange.com/questions/22901/reading-all-bytes-from-a-file
static BytesContainer bytes_from_file(char const* filename) {
	// open file at end
	std::ifstream input_stream( filename, std::ios::binary|std::ios::ate );
	if( !input_stream ) {
#ifdef LOGGING
		LOG(ERROR) << "Could not read from file";
		return BytesContainer();
#endif
	}

	// get file size
	std::ifstream::pos_type end_of_file = input_stream.tellg();

	// create new container of that size
	BytesContainer c(end_of_file);

	// read from the beginning of the file
	input_stream.seekg(0, std::ios::beg);

	input_stream.read((char*) c.data(), end_of_file );

	input_stream.close();

	return c;
}

#endif /* !__file_ops_h__ */

