/*
 * net_class.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __net_class_h__
#define __net_class_h__

#include "networkmuncher/util/logging.h"

class NetClass : public Logging {
	public:
		static const size_t IN = 1;

		NetClass( size_t net_class = IN) : net_class(net_class) {} 

		friend class NetClassConvert;

		bool operator==( const NetClass& other ) const {
			return this->net_class == other.net_class;
		}
		
		virtual ~NetClass() { }

		std::string stringify_object() const {
			std::stringstream info;
			info << net_class;
			return info.str();
		}

	private:
		size_t net_class;
};

#endif /* !__net_class_h__ */

