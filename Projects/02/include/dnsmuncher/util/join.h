/*
 * join.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __join_h__
#define __join_h__

#include <vector>
#include <string>
#include <boost/optional.hpp>

typedef std::vector<std::string> definite_container;
typedef boost::optional< definite_container > maybe_container;

/**
 * Join two containers.
 */
template <class T>
std::vector<T> join( const std::vector<T> first, const std::vector<T> second ) {
	std::vector<T> joined;
	joined.reserve( first.size() + second.size() );
	joined.insert( joined.end(), first.begin(), first.end() );
	joined.insert( joined.end(), second.begin(), second.end() );
	return joined;
}

/**
 * Joins two possibly valid containers.  If both are invalid, return an invalid
 * container.  If one is valid, return that container. Otherwise if both
 * containers a valid join them together.
 */
inline maybe_container maybe_join( const maybe_container& first, const maybe_container& second ) {

	if( !first && !second ) {
		maybe_container r;
		return r;
	}

	definite_container combined;

	if( first ) {
		combined = join( combined, *first );
	}

	if( second ) {
		combined = join( combined, *second );
	}

	return combined;

}

#endif /* !__join_h__ */

