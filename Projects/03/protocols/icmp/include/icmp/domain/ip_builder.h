/*
 * ip_builder.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef IP_BUILDER_H
#define IP_BUILDER_H

#include "ip.h"
#include "ptr_types.h"

class IpBuilder {
	public:
		Ip build() {
			// TODO
			return Ip();
		}

		IpPtr build_ptr() {
			// TODO
			return IpPtr( new Ip() );
		}

	private:
		Ip variable_holder;
};

#endif /* !IP_BUILDER_H */

