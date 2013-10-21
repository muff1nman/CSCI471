/*
 * net_class_convert.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __net_class_convert_h__
#define __net_class_convert_h__

#include "convert_all.h"
#include "dnsmuncher/util/byte/convert.h"

class NetClassConvert : public Convert {
	public:
		NetClassConvert(const NetClass& net_class) : net_class(net_class) { }
		virtual BytesContainer to_data() const {
			return convert_big_endian<DNS::GENERIC_HEADER_FIELD_LENGTH / BITS_PER_BYTE>(std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH>( this->net_class.net_class ));
		}

	protected:
		const NetClass& net_class;

};

#endif /* !__net_class_convert_h__ */

