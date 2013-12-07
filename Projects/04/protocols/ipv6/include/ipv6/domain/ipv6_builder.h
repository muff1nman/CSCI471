/*
 * ipv6_builder.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef IPV6_BUILDER_H
#define IPV6_BUILDER_H

#include "ipv6.h"
#include "ptr_types.h"

#include "networkmuncher/util/byte/byte.h"
#include "networkmuncher/util/index.h"

#include "ipv6/data/ipv6_addr_convert.h"

#include <stdlib.h>
#include <time.h>
#include <string>

/**
 * Pretty self explanatory class here.  However, one thing to clarify.  Some
 * default options will be set for you here if you do not set the value
 * yourself.  However, some values will also be set by the kernel after we
 * convert an Ipv6 to a packet and hand it over to the socket library. See raw(7)
 * for more info on that end.  The following table was copied from raw(7):
 *
 * ┌───────────────────────────────────────────────────┐
 * │IPV6 Header fields modified on sending by IPV6_HDRINCL │
 * ├──────────────────────┬────────────────────────────┤
 * │IPV6 Checksum           │Always filled in.           │
 * ├──────────────────────┼────────────────────────────┤
 * │Source Address        │Filled in when zero.        │
 * ├──────────────────────┼────────────────────────────┤
 * │Packet Id             │Filled in when zero.        │
 * ├──────────────────────┼────────────────────────────┤
 * │Total Length          │Always filled in.           │
 * └──────────────────────┴────────────────────────────┘
 *
 * There are some other fields that you should fill in.  You can check that
 * these fields have been all set (but not necessarily with valid values) by
 * calling is_valid() before calling build().  To that end, however, even if
 * is_valid() returns false, build() will still attempt to return an object for
 * you.  You just may run into problems later if you don't know what you are
 * doing.  Actually you will probably still run into problems, but at least I
 * warned you here.
 *
 */
class Ipv6Builder {

	public:
		static const unsigned int IPV6 = 4;
		static const unsigned int HEADER_LENGTH_WITHOUT_OPTIONS = 5;

		Ipv6Builder& set_version(Ipv6::Version version) {
			variable_holder.version = version;
			return do_common();
		}

		Ipv6Builder& set_type_of_service(Ipv6::Tos tos) {
			variable_holder.tos = tos;
			return do_common();
		}

		Ipv6Builder& set_flow(Ipv6::Flow flow) {
			variable_holder.flow = flow;
			return do_common();
		}

		Ipv6Builder& set_total_length(Ipv6::TotalLength total_length) {
			variable_holder.total_length = total_length;
			return do_common();
		}

		Ipv6Builder& set_next_header(const Ipv6::NextHeader& header) {
			variable_holder.next_header = header;
			return do_common();
		}

		Ipv6Builder& set_hop_limit(const Ipv6::HopLimit limit) {
			variable_holder.hop_limit = limit;
			return do_common();
		}

		Ipv6Builder& set_source_addr(const Ipv6::Addr& addr) {
			variable_holder.source_addr = addr;
			return do_common();
		}

		Ipv6Builder& set_source_addr(const std::string& ipv6_addr) {
			return set_source_addr(Ipv6AddrConvert(ipv6_addr).to_bitset());
		}

		Ipv6Builder& set_dest_addr(const Ipv6::Addr& addr) {
			variable_holder.dest_addr = addr;
			return do_common();
		}

		Ipv6Builder& set_dest_addr(const std::string& ipv6_addr) {
			return set_dest_addr(Ipv6AddrConvert(ipv6_addr).to_bitset());
		}



		// No options for you!
		// Ipv6Builder& set_options() ---

		bool is_valid() {
			return 
				// TODO
				true; // why? cause I wanted the three lines above nice and symmetric :)
		}

		Ipv6 build() {
			set_default_fields();
			return Ipv6(variable_holder);
		}

		Ipv6Ptr build_ptr() {
			set_default_fields();
			return Ipv6Ptr( new Ipv6(variable_holder) );
		}

	private:
		Ipv6 variable_holder;

		Ipv6Builder& do_common() {
			return *this;
		}

		/**
		 * sets fields whose default values need to be set because the default 
		 * value is not zero
		 */
		void set_default_fields() {
			// TODO
		}

};

#endif /* !IPV6_BUILDER_H */

