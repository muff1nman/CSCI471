/*
 * icmp_convert.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ICMP_CONVERT_H
#define ICMP_CONVERT_H

#include "networkmuncher/data/convert.h"

#include "icmp/domain/domain.h"

class ICMPConvert : public Convert {
	public:
		ICMPConvert(RawPtr raw) : icmp(raw) { }
		virtual BytesContainer to_data() const { /*TODO*/ }

	private:
		RawPtr icmp;
};

#endif /* !ICMP_CONVERT_H */

