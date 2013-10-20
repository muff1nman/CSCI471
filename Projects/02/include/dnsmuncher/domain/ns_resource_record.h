/*
 * ns_resource_record.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __ns_resource_record_h__
#define __ns_resource_record_h__

#include "resource_record.h"

class NsResourceRecord : public ResourceRecord {
	public:
		NsResourceRecord( const Name& aname, const BytesContainer& data, QType type, NetClass aclass, ttl_number ttl, rdata_length_number rdlength, Name ns) : ResourceRecord(aname, data, type, aclass, ttl, rdlength), ns(ns) {
		}

		NsResourceRecord( const ResourceRecord& parent, const Name& ns) : ResourceRecord(parent), ns(ns) {
		}

		Name get_ns() const {
			return ns;
		}

		virtual ~NsResourceRecord() { }

	protected:
		Name ns;
};

#endif /* !__ns_resource_record_h__ */

