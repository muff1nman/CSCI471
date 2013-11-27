/*
 * question.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_question_h__
#define __dns_question_h__

#include "name.h"
#include "qtype.h"
#include "net_class.h"

#include "networkmuncher/util/logging.h"

#include <string>

class Question : public Logging {
	public:
		Question( Name domain_name, QType type = QType(), NetClass qclass =
				NetClass() ) : qname(domain_name), type(type), qclass(qclass) {}

		friend class QuestionConvert;

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

		Type get_type() const {
			return type;
		}

		Name get_name() const {
			return qname;
		}

	private:
		Name qname;
		QType type;
		NetClass qclass;

};

#endif /* !__dns_question_h__ */

