/*
 * resource_record_convert.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __resource_record_convert_h__
#define __resource_record_convert_h__

#include "convert_all.h"

class ResourceRecordConvert : public Convert {
	public:
		ResourceRecordConvert( const ResourceRecord& resoure_record ) : resource_record(resource_record) { }
		virtual BytesContainer to_data() const {
			BytesContainer c;
			c = join(c, NameConvert(this->resource_record.aname).to_data());
			c = join(c, TypeConvert(this->resource_record.type).to_data());
			c = join(c, NetClassConvert(this->resource_record.aclass).to_data());
			c = join(c, convert_big_endian<DNS::GENERIC_HEADER_FIELD_LENGTH /
					BITS_PER_BYTE>(
						std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH>(this->resource_record.ttl)));
			c = join(c, convert_big_endian<DNS::GENERIC_HEADER_FIELD_LENGTH /
					BITS_PER_BYTE>(
						std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH>(this->resource_record.rdlength)));
			c = join(c, this->resource_record.rdata);

			return c;
		}

	protected:
		const ResourceRecord& resource_record;
};

#endif /* !__resource_record_convert_h__ */

