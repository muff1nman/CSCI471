/*
 * parse_hint.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef PARSE_HINT_H
#define PARSE_HINT_H

#include "networkmuncher/domain/protocol_types.h"

class ParseHint {
	public:
		ParseHint(bool should_parse, int suggested_protocol = PType::UNKNOWN ) :
			should_parse(should_parse), suggested_protocol(suggested_protocol) { }

		bool get_should_parse() {
			return this->should_parse;
		}

		int get_suggested_protocol() {
			return this->suggested_protocol;
		}

	protected:
		bool should_parse;
		int suggested_protocol;

};

#endif /* !PARSE_HINT_H */

