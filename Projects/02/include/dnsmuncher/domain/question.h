/*
 * question.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __question_h__
#define __question_h__

#include "name.h"
#include "qtype.h"
#include "net_class.h"
#include <string>
#include "dnsmuncher/util/logging.h"

class Question : public Logging {
	public:
		Question( Name domain_name, QType type = QType(), NetClass qclass =
				NetClass() ) : qname(domain_name), type(type), qclass(qclass) {}

		/** 
		 * For testing purposes
		 */
		bool operator==( const Question& other ) const {
			return this->qname == other.qname &&
				this->type == other.type &&
				this->qclass == other.qclass;
		}

		std::string stringify_object() const {
			std::stringstream info;
			info << "name: " << qname.to_string() << list_sep;
			info << "type: " << type.to_string() << list_sep;
			info << "class: " << qclass.to_string() << sep;
			return info.str();
		}

	private:
		Name qname;
		QType type;
		NetClass qclass;

};

#endif /* !__question_h__ */

