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
#include "dnsmuncher/util/byte/byte.h"

#include <vector>
#include <algorithm>

class ResourceRecord {
	public:
		ResourceRecord( Name aname = ".", QType type = QType(), NetClass aclass = NetClass() ) : aname(aname), type(type), aclass(aclass) {}

		bool operator==( const ResourceRecord& other ) const {
			return this->aname == other.aname &&
				this->type == other.type &&
				this->aclass == other.aclass &&
				this->ttl == other.ttl &&
				this->rdlength == other.rdlength;
				this->rdata.size() == other.rdata.size() &&
				std::equal( this->rdata.begin(), this->rdata.end(), other.rdata.begin() );
		}

	private:
		Name aname;
		QType type;
		NetClass aclass;
		unsigned int ttl;
		unsigned int rdlength;
		BytesContainer rdata;
};

#endif /* !__resource_record_h__ */

