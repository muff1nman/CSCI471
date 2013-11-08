/*
 * type_convert.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_type_convert_h__
#define __dns_type_convert_h__

#include "convert_all.h"

class TypeConvert : public Convert {
	public:
		TypeConvert(const Type& type) : type(type) { }
		virtual BytesContainer to_data() const {
			return convert_big_endian<DNS::GENERIC_HEADER_FIELD_LENGTH / BITS_PER_BYTE>(std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH>( this->type.type ));
			return BytesContainer();
		}

	protected:
		const Type& type;

};

#endif /* !__dns_type_convert_h__ */

