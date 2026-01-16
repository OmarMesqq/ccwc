#include <stdio.h>
#include <wctype.h>
#include <stdlib.h>
#include "libs/libcutilities/cutilities.h"

static void print_bytes(FILE* f);
static void print_lines(FILE* f);
static void print_words(FILE* f);
static void print_characters(FILE* f);

/**
 * Output formatter for every `wc`/`ccwc` count.
 * Every column has a single whitespace to its left
 * and is right-justified by the width of the count
 */
static char const format_sp_int[] = " %*s";
/**
 * Output formatter for the filename, when supplied.
 * `wc` prints the filename as the last column with
 * a single whitespace to its left as well
 */
static char const format_filename_int[] = " %s";

int main(int argc, char** argv) {
    
    if (argc == 3) {    // 'ccwc -flag <file>'
        const char* optionsArg = argv[1];
        const char* filename = argv[2];
        if (optionsArg[0] == '-') {
            if (!filename) {
                fprintf(stderr, "expected filename for option %s\n", optionsArg);
                return -1;
            }
            FILE* f = fopen(filename, "r");
            if (!f) {
                fprintf(stderr, "failed to open file: %s\n", filename);
                return -1;
            }

            if (optionsArg[1] == 'c') {
                print_bytes(f);
            }

            if (optionsArg[1] == 'l') {
                print_lines(f);
            }

            if (optionsArg[1] == 'w') {
                print_words(f);
            }

            if (optionsArg[1] == 'm') {
                print_characters(f);
            }
            printf(format_filename_int, filename);
            putchar('\n');
        }
    } else if (argc == 2) {
        const char* firstArg = argv[1];
        if (!firstArg) {
            fprintf(stderr, "expected a second CLI argument.\n");
            return -1;
        }
        
        if (firstArg[0] != '-') { // 'ccwc <file>'
            FILE* f = fopen(firstArg, "r");
            if (!f) {
                fprintf(stderr, "failed to open file: %s\n", firstArg);
                return -1;
            }
            print_lines(f);
            print_words(f);
            print_bytes(f);
            printf(format_filename_int, firstArg);
            putchar('\n');
        } else { // 'ccwc -flag'
            char flag = firstArg[1];
            if (!flag) {
                fprintf(stderr, "no flags passed.Aborting.\n");
                return -1;
            }

            switch (flag) {
                case 'c':
                    print_bytes(stdin);
                    break;
                case 'l':
                    print_lines(stdin);
                    break;
                case 'w':
                    print_words(stdin);
                    break;
                case 'm':
                    print_characters(stdin);
                    break;
                default:
                    fprintf(stderr, "unknown flag %c\n", flag);
                    return -1;
            }
            putchar('\n');
        }
    } else {
        char* usage = "usage:\n1. ccwc -flag <file>\n2. ccwc <file>\n3. ccwc -flag (for stdin processing)\n";
        fprintf(stderr, "%s", usage);
        return -1;
    }

    return 0;
}

/**
 * Prints formatted **byte count** of a file `f` to `stdout`
 */
static void print_bytes(FILE* f) {
    long length = 0;
    int c = 0;
    while ((c = fgetc(f)) != EOF) {
        ++length;
    }
    rewind(f);

    unsigned long width = get_number_width(length);
    char* s = numtoi(length, width);
    if (!s) {
        fprintf(stderr, "malloc failed\n");
        return;
    }

    // Enforce minimum column width
    if (width < 7) {
        width = 7;
    }

    printf(format_sp_int, (int) width, s);
    free(s);
}

/**
 * Prints formatted **line count** of a file `f` to `stdout`
 */
static void print_lines(FILE* f) {
    unsigned size = 0;
    int c = 0;
    while ((c = fgetc(f)) != EOF) {
        if (c == '\n') ++size;
    }
    rewind(f);

    unsigned long width = get_number_width(size);
    char* s = numtoi(size, width);
    if (!s) {
        fprintf(stderr, "malloc failed\n");
        return;
    }

    // Enforce minimum column width
    if (width < 7) {
        width = 7;
    }

    printf(format_sp_int, (int) width, s);
    free(s);
}

/**
 * Prints formatted **word count** of a file `f` to `stdout`.
 * 
 * Pursuant to `man wc`: a word is any sequence of chars
 * whose call to `iswspace` does NOT return true.
 * Implements a simple FSM to handle state transitions
 * (word->end word->etc).
 */
static void print_words(FILE* f) {
    #define OUT 0   // not in a word
    #define IN 1    // inside a word
    
    unsigned char state = OUT;
    int c = 0;
    unsigned count = 0;

    /**
     * INPUT        TRANSITION  ACTION
     * blank        *->OUT      end any previous word, if any
     * non-blank    *->IN       start a new word if outside of one
     */
    while ((c = fgetc(f)) != EOF) {
        if (iswspace(c)) {
            state = OUT;
        }
        else if (state == OUT) {
            state = IN;
            ++count;
        }
    }
    rewind(f);

    unsigned long width = get_number_width(count);
    char* s = numtoi(count, width);
    if (!s) {
        fprintf(stderr, "malloc failed\n");
        return;
    }

    // Enforce minimum column width
    if (width < 7) {
        width = 7;
    }

    printf(format_sp_int, (int) width, s);
    free(s);
}
/**
 * Prints formatted **character count** of a file `f` to `stdout`.
 * 
 * **Assumes file is UTF-8 encoded**, handling single and multi byte sequences.
 */
static void print_characters(FILE* f) {
    int c = 0;
    unsigned count = 0;
    unsigned char inMultiByteCh = 0;
    unsigned char multiByteChSize = 0;

    while ((c = fgetc(f)) != EOF) {
        // single byte UTF-8 characters have MSB off
        if (((c >> 7) & 1) == 0) {
            ++count;
            continue;
        }
        // here, we are at a start or continuation multibyte character

        if (inMultiByteCh) {
            if (--multiByteChSize == 0) {
                ++count;
                inMultiByteCh = 0;
            }
            continue;
        }

        if ((c & 0xE0) == 0xC0) {          /* 110xxxxx → 2‑byte */
            multiByteChSize = 1;    // 2 - current one
        } else if ((c & 0xF0) == 0xE0) {    /* 1110xxxx → 3‑byte */
            multiByteChSize = 2;        // 3 - current one
        } else if ((c & 0xF8) == 0xF0) {    /* 11110xxx → 4‑byte */
            multiByteChSize = 3;    // 4 - current one
        }
        inMultiByteCh = 1;
    }
    rewind(f);

    unsigned long width = get_number_width(count);
    char* s = numtoi(count, width);
    if (!s) {
        fprintf(stderr, "malloc failed\n");
        return;
    }

    // Enforce minimum column width
    if (width < 7) {
        width = 7;
    }

    printf(format_sp_int, (int) width, s);
    free(s);
}
