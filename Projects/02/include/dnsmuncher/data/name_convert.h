/*
 * name_convert.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __name_convert_h__
#define __name_convert_h__

#include "convert_all.h"
#include "dnsmuncher/domain/name.h"

class NameConvert : public Convert {
	public:
		NameConvert(const Name& name) : iname(name) { }
		virtual BytesContainer to_data() const {
			BytesContainer c;
			std::vector<std::string> labels = this->iname.get_labels();
			for( size_t i = 0; i < labels.size(); ++i ) {
				c.push_back( (Byte) labels.at(i).size() );
				c.insert( c.end(), labels.at(i).begin(), labels.at(i).end());
			}
			c.push_back( (Byte) 0 );
			return c;
		}

	protected:
		Name iname;

};

#endif /* !__name_convert_h__ */

