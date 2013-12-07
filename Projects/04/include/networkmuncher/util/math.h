/*
 * math.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __math_h__
#define __math_h__

#include <numeric>

template <class T>
double average(const std::vector<T>& nums) {
	double sum = std::accumulate(nums.begin(), nums.end(), 0.0);
	return sum / (double) nums.size();
}

#endif /* !__math_h__ */

