/*
 * iterator.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ITERATOR_H
#define ITERATOR_H

template <class ForwardIterator, class Distance>
inline ForwardIterator next(ForwardIterator it, Distance d) {
	ForwardIterator i = it;
	std::advance(i, d);
	return i;
}

#endif /* !ITERATOR_H */

