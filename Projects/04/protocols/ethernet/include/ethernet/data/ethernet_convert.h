/*
 * ip_convert.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ETHERNET_CONVERT_H
#define ETHERNET_CONVERT_H

#include "networkmuncher/data/convert.h"
#include "ethernet/domain/domain.h"
#include "networkmuncher/util/logging.h"

class EthernetConvert : public Convert {
	public:
		EthernetConvert(EthernetPtr ptr) : ip(ptr) { }

		virtual BytesContainer to_data() const {
			BytesContainer bytes;
			// TODO
			return bytes;
		}

	private:
		EthernetPtr ip;
};

#endif /* !ETHERNET_CONVERT_H */

