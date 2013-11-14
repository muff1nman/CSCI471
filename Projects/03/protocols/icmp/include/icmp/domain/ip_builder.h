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
#include "networkmuncher/util/index.h"

#include <stdlib.h>
#include <time.h>

/**
 * Pretty self explanatory class here.  However, one thing to clarify.  Some
 * default options will be set for you here if you do not set the value
 * yourself.  However, some values will also be set by the kernel after we
 * convert an Ip to a packet and hand it over to the socket library. See raw(7)
 * for more info on that end.  The following table was copied from raw(7):
 *
 * ┌───────────────────────────────────────────────────┐
 * │IP Header fields modified on sending by IP_HDRINCL │
 * ├──────────────────────┬────────────────────────────┤
 * │IP Checksum           │Always filled in.           │
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
class IpBuilder {

	public:
		static const unsigned int IPV4 = 4;
		static const unsigned int HEADER_LENGTH_WITHOUT_OPTIONS = 20;

		IpBuilder& set_version(Ip::Version version) {
			variable_holder.version = version;
			version_set = true;
			return do_common();
		}

		IpBuilder& set_header_length(Ip::HeaderLength header_length) {
			variable_holder.header_length = header_length;
			header_length_set = true;
			return do_common();
		}

		IpBuilder& set_type_of_service(Ip::Tos tos) {
			variable_holder.tos = tos;
			return do_common();
		}

		IpBuilder& set_total_length(Ip::TotalLength total_length) {
			variable_holder.total_length = total_length;
			return do_common();
		}

		IpBuilder& set_id(Ip::Id id) {
			variable_holder.id = id;
			return do_common();
		}

		IpBuilder& set_flags(Ip::Flags flags) {
			variable_holder.flags = flags;
			return do_common();
		}

		IpBuilder& set_dont_fragment(bool value = true) {
			set_with_reverse_index( 
					variable_holder.flags,
					+Ip::DONT_FRAGMENT_POS_FROM_LEFT, 
					value );
			return do_common();
		}

		IpBuilder& set_more_fragments(bool value = true ) {
			set_with_reverse_index(
				variable_holder.flags,
				+Ip::MORE_FRAGMENTS_POS_FROM_LEFT,
				value);
			return do_common();
		}

		IpBuilder& set_fragment_offset(Ip::FragOffset fo) {
			variable_holder.frag_offset = fo;
			return do_common();
		}

		IpBuilder& set_ttl(Ip::TTL ttl) {
			variable_holder.ttl = ttl;
			ttl_set = true;
			return do_common();
		}

		IpBuilder& set_protocol(Ip::Protocol protocol) {
			variable_holder.protocol = protocol;
			protocol_set = true;
			return do_common();
		}

		IpBuilder& set_checksum(Ip::Checksum checksum) {
			variable_holder.checksum = checksum;
			return do_common();
		}

		IpBuilder& set_source_addr(Ip::SourceAddr addr) {
			variable_holder.source_addr = addr;
			return do_common();
		}

		IpBuilder& set_dest_addr(Ip::DestAddr addr) {
			variable_holder.dest_addr = addr;
			dest_addr_set = true;
			return do_common();
		}

		// No options for you!
		// IpBuilder& set_options() ---

		bool is_valid() {
			return 
				ttl_set &&
				protocol_set &&
				dest_addr_set &&
				true; // why? cause I wanted the three lines above nice and symmetric :)
		}

		Ip build() {
			set_default_fields();
			return Ip(variable_holder);
		}

		IpPtr build_ptr() {
			set_default_fields();
			return IpPtr( new Ip(variable_holder) );
		}

	private:
		Ip variable_holder;

		IpBuilder& do_common() {
			return *this;
		}

		/**
		 * sets fields whose default values need to be set because the default 
		 * value is not zero
		 */
		void set_default_fields() {
			if( ! version_set ) {
				set_version(IPV4);
			}

			if( ! header_length_set ) {
				set_header_length(HEADER_LENGTH_WITHOUT_OPTIONS);
			}

		}

		/* 
		 * Keep track of which varibles have been set
		 */
		bool version_set, 
			 header_length_set,
			 ttl_set,
			 protocol_set,
			 dest_addr_set;

};

#endif /* !IP_BUILDER_H */

