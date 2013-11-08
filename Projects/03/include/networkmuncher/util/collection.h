/*
 * collection.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __collection_h__
#define __collection_h__

#include <boost/optional.hpp>

template <class T>
boost::optional<T> maybe_first( const std::vector<T>& list ) {
	boost::optional<T> result;
	if( !list.empty() ) {
		result = *(list.begin());
	}
	return result;
}

#endif /* !__collection_h__ */

