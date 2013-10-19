/*
 * name_convert.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __name_convert_h__
#define __name_convert_h__

#include "convert_all.h"

class NameConvert : public Convert {
	public:
		NameConvert(const Name& name) : name(name) { }
		virtual BytesContainer to_data() const {
			BytesContainer c;
			for( size_t i = 0; i < name.labels.size(); ++i ) {
				c.push_back( (Byte) name.labels.at(i).size() );
				c.insert( c.end(), name.labels.at(i).begin(), name.labels.at(i).end());
			}
			c.push_back( (Byte) 0 );
			return c;
		}

	protected:
		const Name& name;

};

#endif /* !__name_convert_h__ */

