/*
 * ns_resource_record.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __ns_resource_record_h__
#define __ns_resource_record_h__

#include "name_resource_record.h"

class NsResourceRecord : public NameResourceRecord {
	public:
		NsResourceRecord( const ResourceRecord& parent, const Name& ns) : NameResourceRecord(parent,ns) { }
		virtual ~NsResourceRecord() { }
};

#endif /* !__ns_resource_record_h__ */

