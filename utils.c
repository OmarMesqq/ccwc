#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

unsigned long get_number_width(unsigned long ul) {
    unsigned long width = 0;
    unsigned long q = 0;  // quotient
    unsigned long D = ul;  // divisor: starts as the given number

    /**
     * Every whole number >= 0, has at least one digit,
     * so a `do...while` seems appropriate as 
     * the width should be 1 at the minimum.
     * 
     * Loop termination condition is whether the divisor reaches zero.
     * As such, right after considering a number has at least one digit (`++width`),
     * we get the quotient of the first or previous number by 10, and set
     * the next divisor as it.
     * 
     * The number 10 has this cool feature that allows breaking down the number in its digits
     * as we count in decimal. To get a number's width we simply count how many iterations
     * it takes to "walk through" all the digits - eventually we'll get a single digit
     * number that divided by 10 yields 0, thus breaking the loop.
     */
    do {
        ++width;
        q = D / 10;
        D = q;
    } while (D != 0);

    
    return width;
}

char* numtoi(unsigned long ul, unsigned long width) {
    unsigned long q = 0;  // quotient
    unsigned long D = 0;  // divisor
    unsigned long r = 0;  // remainder

    char* str = (char*) malloc(width * sizeof(char));
    if (!str) {
        return NULL;
    }

    int i = width - 1;
    D = ul;

    //TODO: stop this hack
    if (D == 0) {
        str[i] = '0';
        ++i;
        str[i] = '\0';
        return str;
    }
    q = D / 10;
    r = D % 10;
    while (1) {
        if (D == 0) {
            break;
        }

        str[i] = r + '0';
        --i;

        D = q;
        q = D / 10;
        r = D % 10;
    }
    
    str[width] = '\0';
    return str;
}
