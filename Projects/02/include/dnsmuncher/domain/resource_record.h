/*
 * resource_record.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __resource_record_h__
#define __resource_record_h__

#include "name.h"
#include "qtype.h"
#include "net_class.h"

class ResourceRecord {

	// TODO clean up rdata (it was possibly allocated with new?)

	private:
		Name aname;
		QType type;
		NetClass aclass;
		unsigned int ttl;
		unsigned int rdlength;
		void* rdata;
};

#endif /* !__resource_record_h__ */

