#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

unsigned long get_number_width(unsigned long ul) {
    unsigned long width = 0;
    unsigned long q = 0;  // quotient
    unsigned long d = ul;  // dividend: starts as the given number

    /**
     * Every whole number >= 0, has at least one digit,
     * so a `do...while` seems appropriate as 
     * the width should be 1 at the minimum.
     * 
     * Loop termination condition is whether the dividend reaches zero.
     * As such, right after considering that a number has at least one digit (`++width`),
     * we get the quotient of the first or previous number by 10, and set
     * the next dividend as it.
     * 
     * The number 10 has this cool feature that allows breaking down the number in its digits
     * as we count in decimal. To get a number's width we simply count how many iterations
     * it takes to "walk through" all the digits - eventually we'll get a single digit
     * number that divided by 10 yields 0, thus breaking the loop.
     */
    do {
        ++width;
        q = d / 10;
        d = q;
    } while (d != 0);

    
    return width;
}

char* numtoi(unsigned long ul, unsigned long width) {
    unsigned long q = 0;  // quotient
    unsigned long d = ul;  // dividend: starts as the given number
    unsigned long r = 0;  // remainder

    char* str = (char*) malloc((width + 1) * sizeof(char));
    if (!str) {
        fprintf(stderr, "numtoi: failed to allocate string to represent number!\n");
        return NULL;
    }

    int i = width - 1;

    //TODO: stop this hack
    if (d == 0) {
        str[i] = '0';
        ++i;
        str[i] = '\0';
        return str;
    }
    q = d / 10;
    r = d % 10;
    while (1) {
        if (d == 0) {
            break;
        }

        str[i] = r + '0';
        --i;

        d = q;
        q = d / 10;
        r = d % 10;
    }
    
    str[width] = '\0';
    return str;
}
