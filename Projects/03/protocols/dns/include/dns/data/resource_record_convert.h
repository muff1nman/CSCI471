/*
 * resource_record_convert.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_resource_record_convert_h__
#define __dns_resource_record_convert_h__

#include "convert_all.h"

#include "dns/domain/resource_record.h"

class ResourceRecordConvert : public Convert {
	public:
		ResourceRecordConvert( const ResourceRecord& resource_record ) : iresource_record(resource_record) { }
		virtual BytesContainer to_data() const {
			BytesContainer c;
			c = join(c, NameConvert(this->iresource_record.get_label_name()).to_data());
			c = join(c, TypeConvert(this->iresource_record.type).to_data());
			c = join(c, NetClassConvert(this->iresource_record.aclass).to_data());
			c = join(c, convert_big_endian<DNS::GENERIC_HEADER_FIELD_LENGTH * 2 /
					BITS_PER_BYTE>(
						std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH * 2>(this->iresource_record.ttl)));
			c = join(c, convert_big_endian<DNS::GENERIC_HEADER_FIELD_LENGTH /
					BITS_PER_BYTE>(
						std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH>(this->iresource_record.rdlength)));
			c = join(c, this->iresource_record.rdata);

			return c;
		}

	protected:
		ResourceRecord iresource_record;
};

#endif /* !__dns_resource_record_convert_h__ */

