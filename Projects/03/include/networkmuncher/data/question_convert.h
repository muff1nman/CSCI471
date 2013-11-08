/*
 * question_convert.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __question_convert_h__
#define __question_convert_h__

#include "convert.h"
#include "networkmuncher/util/byte/convert.h"
#include "networkmuncher/util/join.h"
#include "networkmuncher/data/name_convert.h"
#include "networkmuncher/data/type_convert.h"
#include "networkmuncher/data/net_class_convert.h"

class QuestionConvert : public Convert {
	public:
		QuestionConvert(const Question& question) : question(question) { }
		virtual BytesContainer to_data() const {
			BytesContainer c;
			c = join(c, NameConvert(this->question.qname).to_data());
			c = join(c, TypeConvert(this->question.type).to_data());
			c = join(c, NetClassConvert(this->question.qclass).to_data());
			return c;;
		}

	protected:
		const Question& question;
};

#endif /* !__question_convert_h__ */
