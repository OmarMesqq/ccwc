#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

unsigned long get_number_width(unsigned long ul) {
    unsigned long width = 0;
    unsigned long q = 0;  // quotient
    unsigned long D = 0;  // divisor

    //TODO: stop this hack
    if (ul == 0) {
        return 1;
    }

    D = ul;
    q = D / 10;
    while (1) {
        if (D == 0) {
            break;
        }
        ++width;
        D = q;
        q = D / 10;
    }
    
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
