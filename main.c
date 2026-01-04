#include <stdio.h>

static void print_bytes(FILE* f, const char* filename);
static void print_lines(FILE* f, const char* filename);

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