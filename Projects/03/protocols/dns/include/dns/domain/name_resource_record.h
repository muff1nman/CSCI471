/*
 * name_resource_record.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_name_resource_record_h__
#define __dns_name_resource_record_h__

#include "resource_record.h"
#include "name.h"

/**
 * A Resource Record with the rdata treated as a Name.
 */
class NameResourceRecord : public ResourceRecord {
	public:
		NameResourceRecord( const Name& aname, const BytesContainer& data, QType type, NetClass aclass, ttl_number ttl, rdata_length_number rdlength, Name name) : ResourceRecord(aname, data, type, aclass, ttl, rdlength), name(name) {
		}

		NameResourceRecord( const ResourceRecord& parent, const Name& name) : ResourceRecord(parent), name(name) {
		}

		Name get_name() const {
			return name;
		}

		virtual ~NameResourceRecord() { }

	protected:
		Name name;
};
#endif /* !__dns_name_resource_record_h__ */

