/*
 * header_producer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __header_producer_h__
#define __header_producer_h__

#include "httpmuncher/response/status.h"
#include "httpmuncher/socket/header_request_consumer.h"
#include "httpmuncher/domain/http_response_header.h"
#include <fstream>
#include <boost/filesystem.hpp>
#include "httpmuncher/util/number.h"

class HeaderProducer: public HeaderRequestConsumer {

	public:
		HeaderProducer( int fd ) : HeaderRequestConsumer(fd) { }

		virtual void run() {
			HeaderRequestConsumer::run();
			std::string to_write = send_back();
			write(socket_fd, to_write.c_str(), to_write.size());
		}

		virtual std::string get_path() {
			return std::string(".") + request_header->get_path();
		}

		virtual bool file_exists() {
			std::string path = get_path();
#ifdef LOGGING
			LOG(INFO) << "Requesting path: " << path;
#endif
			return boost::filesystem::exists( path.c_str() );
		}

		virtual std::string body_contents() {
			std::string path = get_path();
			std::ifstream ifs(path.c_str());
			return std::string( (std::istreambuf_iterator<char>(ifs) ),
					(std::istreambuf_iterator<char>() ));
		}

		virtual std::string send_back() {
			HttpResponseHeader h;

			if( file_exists() ) {
				std::string content = body_contents();
				h.set_status(HTTP::OK);
				h.set("Content-Length", NumberToString(content.length()));
				h.set("Content-Type", "text/text");
				return h.as_socket_data() + content;
			} else {
				h.set("Content-Length", "91");
				h.set("Content-Type", "text/html");
				return h.as_socket_data() + HTTP::debug_404_html;
			}

		}

		virtual ~HeaderProducer() { /*noop*/ }

};

#endif /* !__header_producer_h__ */

