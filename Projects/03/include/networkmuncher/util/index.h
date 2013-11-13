/*
 * index.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef INDEX_H
#define INDEX_H

/**
 * Reverses a given index to a given sized structure/array/whatever.  It is
 * assumed that this indexing is zero based.  For example consider the following
 * array
 *
 *  [0,1,2,3,4]
 *  given: index = 1 and size = 5
 *  the return value would be 3
 */
template <class Numeric>
inline Numeric reverse_index(const Numeric& index, const Numeric& size) {
	return (size - 1) - index;
}

template <class Numeric, class Container, class Type>
inline Type set_with_reverse_index(Container& c, const Numeric& index, const Numeric& size, const Type& t) {
	return c[reverse_index(index,size)] = t;
}

template <class Numeric, class Container, class Type>
inline Type set_with_reverse_index(Container& c, const Numeric& index, const Type& t) {
	return set_with_reverse_index(c, index, c.size(), t);
}

#endif /* !INDEX_H */

