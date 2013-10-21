/*
 * name.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __name_h__
#define __name_h__

#include <vector>
#include <string>
#include <algorithm>

#include "dnsmuncher/util/split.h"
#include "dnsmuncher/util/logging.h"

class Name : public Logging {
	public:
		Name() { }

		Name( const char* string ) {
			this->labels = split_name(std::string(string));
		}

		Name( const std::string& domain_name ) {
			this->labels = split_name( domain_name );
		}

		Name( const std::vector<std::string> name ) : labels(name) { }

		bool operator==( const Name& other ) const {
			return this->labels.size() == other.labels.size() &&
				std::equal( this->labels.begin(), this->labels.end(), other.labels.begin() );
		}

		std::string to_string() const {
			std::stringstream info;
			for( size_t i = 0; i < labels.size(); ++i ) {
				info << labels.at(i) << ".";
			}
			return info.str();
		}

		std::string stringify_object() const {
			std::stringstream info;
			info << "labels: ";
			info << this->to_string();
			return info.str();
		}

		std::vector<std::string> get_labels() const {
			return labels;
		}

	private:
		std::vector<std::string> labels;

};

#endif /* !__name_h__ */

