/*
 * byte.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __byte_h__
#define __byte_h__

#include <bitset>
#include <string>
#include <vector>

#include "dnsmuncher/util/logging.h"

#define BITS_PER_BYTE 8

typedef unsigned char Byte;
typedef std::vector<Byte> Bytes;

class BytesContainer {
	public:
		BytesContainer() {
		}

		BytesContainer(Bytes data) {
			this->_data = data;
		}

		BytesContainer(Bytes data, size_t size) {
#ifdef LOGGING
			LOG(WARNING) << "Deprecated";
#endif
			this->_data = data;
		}

		Byte* data() {
			return &(this->_data[0]);
		}

		const Byte* data() const {
			return &(this->_data[0]);
		}

		void resize(size_t size) {
			return _data.resize(size);
		}

		size_t size() const {
			return this->_data.size();
		}

	private:
		Bytes _data;
};


#endif /* !__byte_h__ */

