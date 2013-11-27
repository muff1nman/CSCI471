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
#include "ip_convert.h"
#include "echo_convert.h"
#include "networkmuncher/util/join.h"
#include "networkmuncher/util/logging.h"

class ICMPConvert : public Convert {
	public:
		ICMPConvert(RawPtr raw) : icmp(raw) { }
		virtual BytesContainer to_data() const {
			return join(IpConvert(icmp->ip).to_data(), EchoConvert(icmp->echo).to_data());
		}

	private:
		RawPtr icmp;
};

#endif /* !ICMP_CONVERT_H */

