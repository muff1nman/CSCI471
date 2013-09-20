/*
 * header_producer.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "httpmuncher/socket/header_producer.h"

void HeaderProducer::run() {
	HeaderRequestConsumer::run();
	std::string to_write = send_back();
	write(socket_fd, to_write.c_str(), to_write.size());
}

std::string HeaderProducer::get_path() {
	return std::string(".") + request_header->get_path();
}

bool HeaderProducer::file_exists() {
	std::string path = get_path();
#ifdef LOGGING
	LOG(INFO) << "Requesting path: " << path;
#endif
	return boost::filesystem::exists( path.c_str() );
}

std::string HeaderProducer::body_contents() {
	std::string path = get_path();
	std::ifstream ifs(path.c_str());
	return std::string( (std::istreambuf_iterator<char>(ifs) ),
			(std::istreambuf_iterator<char>() ));
}

std::string HeaderProducer::error_contents() {
	return HTTP::debug_404_html;
}

std::string HeaderProducer::send_back() {
	HttpResponseHeader h;
	std::string content;
	std::string type;

	if( file_exists() ) {
		h.set_status( HTTP::OK );
		// TODO create a new datatype binding content to type
		content = body_contents();
		type  = mime_type(boost::filesystem::extension(get_path()));
	} else {
		h.set_status( HTTP::NOT_FOUND );
		content = error_contents();
		type = "text/html";
	}

	h.set("Content-Length", NumberToString(content.length()));
	h.set("Content-Type", type);

	return h.as_socket_data() + content;
}



