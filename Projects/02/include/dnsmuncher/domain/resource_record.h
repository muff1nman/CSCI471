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
#include "dnsmuncher/util/byte/print.h"
#include "dnsmuncher/util/logging.h"

#include <vector>
#include <algorithm>

class ResourceRecord {
	public:
		ResourceRecord( const Name& aname, const BytesContainer& data, QType type = QType(), NetClass aclass = NetClass(), ttl_number ttl = 0) : aname(aname), rdata(data), type(type), aclass(aclass), ttl(ttl) {
			rdlength = data.size();
		}

		ResourceRecord( const Name& aname, const BytesContainer& data, QType type, NetClass aclass, ttl_number ttl, rdata_length_number rdlength) : aname(aname), rdata(data), type(type), aclass(aclass), ttl(ttl), rdlength(rdlength) {
		}

		friend class ResourceRecordConvert;

		bool operator==( const ResourceRecord& other ) const {
            bool value = this->aname == other.aname &&
				this->type == other.type &&
				this->aclass == other.aclass &&
				this->ttl == other.ttl &&
				this->rdlength == other.rdlength &&
				this->rdata.size() == other.rdata.size() &&
				std::equal( this->rdata.begin(), this->rdata.end(), other.rdata.begin() );
            return value;
		}

		std::string to_string() const {
			std::stringstream info;
			info << "name: " << aname.to_string() << list_sep;
			info << "type: " << type.to_string() << list_sep;
			info << "class: " << aclass.to_string() << list_sep;
			info << "ttl: " << ttl << list_sep;
			info << "rd length: " << rdlength << list_sep;
			info << "rdata: " << nested_start << std::endl;
			info << demaria_util::to_string( rdata ) << std::endl;
			info <<  nested_finish;
			return info.str();
		}

		BytesContainer get_data() const {
			return this->rdata;
		}

		Type get_type() const {
			return this->type;
		}

		virtual ~ResourceRecord() { }
		

	protected:
		Name aname;
		BytesContainer rdata;
		Type type;
		NetClass aclass;
		ttl_number ttl;
		rdata_length_number rdlength;
};

#endif /* !__resource_record_h__ */

