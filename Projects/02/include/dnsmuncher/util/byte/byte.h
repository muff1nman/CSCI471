/*
 * byte.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __byte_h__
#define __byte_h__

#include <boost/shared_ptr.hpp>
#include <bitset>
#include <string>

#include "dnsmuncher/util/logging.h"

#define BITS_PER_BYTE 8

typedef unsigned char Byte;
typedef boost::shared_ptr<Byte> Bytes;

class BytesContainer {
	public:
		BytesContainer() {
			this->_size = 0;
		}

		BytesContainer(Bytes data) {
			set_data( data );
		}

		BytesContainer(Bytes data, size_t size) {
			set_data( data, size );
		}

		void set_data( Bytes data ) {
			this->_data = data;
		}

		void set_data( Bytes data, size_t size ) {
			this->_data = data;
			this->_size = size;
		}

		Byte* data() const {
			return _data.get();
		}

		size_t size() const {
			return _size;
		}

	private:
		size_t _size;
		Bytes _data;
};


#endif /* !__byte_h__ */

