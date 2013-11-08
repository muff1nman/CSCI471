/*
 * type.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __type_h__
#define __type_h__

#include "networkmuncher/util/logging.h"

class Type : public Logging {
	public:
		static const size_t A = 1;
		static const size_t NS = 2;
		static const size_t CNAME = 5;
		static const size_t SOA = 6;
		static const size_t ANY = 255;

		Type( size_t type ) : type(type) { }

		friend class TypeConvert;
		
		bool operator==( const Type& other ) const {
			return this->type == other.type;
		}

		bool operator==( const size_t other ) const {
			return this->type == other;
		}

		operator size_t() {
			return type;
		}

		std::string stringify_object() const {
			std::stringstream info;
			info << type;
			return info.str();
		}

	protected:
		size_t type;
};

#endif /* !__type_h__ */

