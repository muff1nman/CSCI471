/*
 * question_convert.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_question_convert_h__
#define __dns_question_convert_h__

#include "convert_all.h"

#include "networkmuncher/util/join.h"

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

#endif /* !__dns_question_convert_h__ */

