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

class Question {
	private:
		Name qname;
		QType type;
		NetClass qclass;

};

#endif /* !__question_h__ */

