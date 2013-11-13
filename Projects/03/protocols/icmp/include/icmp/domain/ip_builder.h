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
#include "networkmuncher/util/byte/byte.h"

class IpBuilder {
	public:

		IpBuilder& set_version(generic_positive_number version) {
			variable_holder.version = Ip::Version(version);
			return do_common();
		}


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

		IpBuilder& do_common() {
			return *this;
		}
};

#endif /* !IP_BUILDER_H */

