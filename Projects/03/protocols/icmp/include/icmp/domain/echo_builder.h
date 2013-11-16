/*
 * echo_builder.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ECHO_BUILDER_H
#define ECHO_BUILDER_H

#include "echo.h"
#include "ptr_types.h"
#include "networkmuncher/util/logging.h"
#include "icmp/data/echo_convert.h"
#include "networkmuncher/util/byte/operations.h"

/**
 * Usage:  set a type, set an identifier, and set a sequence number.  Other
 * fields will be set to default values or calculated
 */
class EchoBuilder {
	public:

		static const unsigned int ECHO_REQUEST = 8;
		static const unsigned int ECHO_REPLY = 0;
		static const unsigned int ECHO_CODE = 0;

		EchoBuilder& set_type(Echo::Type type) {
			variable_holder.type = type;
			return do_common();
		}

		EchoBuilder& set_request_type() {
			return set_type(ECHO_REQUEST);
		}

		EchoBuilder& set_reply_type() {
			return set_type(ECHO_REPLY);
		}

		EchoBuilder& set_code(Echo::Code code) {
			variable_holder.code = code;
			code_set = true;
			return do_common();
		}

		EchoBuilder& set_checksum(Echo::Checksum checksum) {
			variable_holder.checksum = checksum;
			checksum_set = true;
			return do_common();
		}

		EchoBuilder& set_identifier(Echo::Identifier id) {
			variable_holder.identifier = id;
			return do_common();
		}

		EchoBuilder& set_sequence_num(Echo::SequenceNum sqn) {
			variable_holder.sequence_num = sqn;
			return do_common();
		}

		EchoBuilder& set_data(Echo::Data data) {
			variable_holder.data = data;
			return do_common();
		}

		Echo build() {
			set_default_fields();
			return Echo(variable_holder);
		}

		EchoPtr build_ptr() {
			set_default_fields();
			return EchoPtr( new Echo(variable_holder) );
		}

	private:
		Echo variable_holder;

		EchoBuilder& do_common() {
			return *this;
		}

		Echo::Checksum calculate_checksum() {

			// ensure checksum is empty
			if( variable_holder.checksum.to_ulong() != 0 ) {
#ifdef LOGGING
				LOG(WARNING) << "Checksum is being overwritten";
#endif
				variable_holder.checksum.reset();
			}

			// build and convert to bytes
			BytesContainer data = EchoConvert(build_ptr()).to_data();

			// calculate ones complement
			return ones_complement_sum<Echo::CHECKSUM_LENGTH / BITS_PER_BYTE>( data );

#ifdef LOGGING
			LOG(ERROR) << "Not yet implemented";
#endif
		}

		void set_default_fields() {
			if( ! code_set ) {
				set_code( ECHO_CODE );
			}
			if( ! checksum_set ) {
				set_checksum(calculate_checksum());
			}
		}

		bool code_set, checksum_set;
};

#endif /* !ECHO_BUILDER_H */

