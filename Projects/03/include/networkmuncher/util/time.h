/*
 * time.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef UTIL_TIME_H
#define UTIL_TIME_H

#include <sys/time.h>

const static int MILLI_PER_UNIT = 1000;
const static int MICRO_PER_MILLI = 1000;
const static int MICRO_PER_UNIT = MILLI_PER_UNIT * MICRO_PER_MILLI;

/* 
 * Subtract the `struct timeval' values X and Y,
 * storing the result in RESULT.
 * Return 1 if the difference is negative, otherwise 0. 
 * http://www.gnu.org/software/libc/manual/html_node/Elapsed-Time.html
*/
int timeval_subtract (struct timeval* result, struct timeval* x, struct timeval* y)
{
	/* Perform the carry for the later subtraction by updating y. */
	if (x->tv_usec < y->tv_usec) {
		int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
		y->tv_usec -= 1000000 * nsec;
		y->tv_sec += nsec;
	}
	if (x->tv_usec - y->tv_usec > 1000000) {
		int nsec = (x->tv_usec - y->tv_usec) / 1000000;
		y->tv_usec += 1000000 * nsec;
		y->tv_sec -= nsec;
	}

	/* Compute the time remaining to wait.
	   tv_usec is certainly positive. */
	result->tv_sec = x->tv_sec - y->tv_sec;
	result->tv_usec = x->tv_usec - y->tv_usec;

	/* Return 1 if result is negative. */
	return x->tv_sec < y->tv_sec;
}

void get_current_time( struct timeval& current_time ) {
	int time_ret_val;

	time_ret_val = gettimeofday(&current_time, NULL);
	if(time_ret_val != 0 ) {
		perror("Could not get time");
		exit(1);
	}
}

double convert_to_seconds( const struct timeval& some_time ) {
	return (double) some_time.tv_sec + (double) some_time.tv_usec / MICRO_PER_UNIT;
}

double get_current_time_in_seconds() {
	struct timeval current_time;
	get_current_time(current_time);
	return convert_to_seconds(current_time);
}

double convert_to_milliseconds( const struct timeval& some_time ) {
	return (double) some_time.tv_sec * MILLI_PER_UNIT + (double) some_time.tv_usec / MICRO_PER_MILLI ;
}

double get_current_time_in_milli_seconds() {
	struct timeval current_time;
	get_current_time(current_time);
	return convert_to_milliseconds(current_time);
}


#endif /* !UTIL_TIME_H */

