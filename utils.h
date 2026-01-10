#ifndef UTILS_H
#define UTILS_H

/**
 * Returns the "width" (amount of digits) of a
 * non-negative whole number `ul`.
 */
unsigned long get_number_width(unsigned long ul);

/**
 * Takes a non-negative whole number `ul` and its `width`
 * and returns the former as a heap-allocated string. 
 */
char* numtoi(unsigned long ul, unsigned long width);

#endif
