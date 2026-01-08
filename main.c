#include <stdio.h>
#include <wctype.h>

#define OUT 0   // not in a word
#define IN 1    // inside a word

static void print_bytes(FILE* f, const char* filename);
static void print_lines(FILE* f, const char* filename);
static void print_words(FILE* f, const char* filename);
static void print_characters(FILE* f, const char* filename);

int main(int argc, char** argv) {
    
    if (argc >= 2) {
        const char* optionsArg = argv[1];
        const char* filename = argv[2];
        if (optionsArg[0] == '-') {
            if (!filename) {
                fprintf(stderr, "expected filename for option %s\n", filename);
                return -1;
            }
            FILE* f = fopen(filename, "r");
            if (!f) {
                fprintf(stderr, "failed to open file: %s\n", filename);
                return -1;
            }

            if (optionsArg[1] == 'c') {
                print_bytes(f, filename);
            }

            if (optionsArg[1] == 'l') {
                print_lines(f, filename);
            }

            if (optionsArg[1] == 'w') {
                print_words(f, filename);
            }

            if (optionsArg[1] == 'm') {
                print_characters(f, filename);
            }
        }
    }

    return 0;
}

static void print_bytes(FILE* f, const char* filename) {
    fseek(f, 0 , SEEK_END);
    long length = ftell(f);
    rewind(f);
    printf("%2c%ld %s\n", ' ', length, filename);
}

static void print_lines(FILE* f, const char* filename) {
    unsigned size = 0;
    int c = 0;
    while ((c = fgetc(f)) != EOF) {
        if (c == '\n') ++size;
    }
    printf("%4c%d %s\n", ' ', size, filename);
}

static void print_words(FILE* f, const char* filename) {
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
    printf("%3c%d %s\n", ' ', count, filename);
}

static void print_characters(FILE* f, const char* filename) {
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

    printf("%2c%d %s\n", ' ', count, filename);
}
