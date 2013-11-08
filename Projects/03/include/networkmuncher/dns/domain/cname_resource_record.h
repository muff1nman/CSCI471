/*
 * cname_resource_record.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_cname_resource_record_h__
#define __dns_cname_resource_record_h__

#include "name_resource_record.h"

class CNameResourceRecord : public NameResourceRecord {
	public:
		CNameResourceRecord( const ResourceRecord& parent, const Name& cname) : NameResourceRecord(parent,cname) { }
		virtual ~CNameResourceRecord() { }
};

#endif /* !__dns_cname_resource_record_h__ */

