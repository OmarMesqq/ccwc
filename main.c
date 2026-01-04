#include <stdio.h>

static void print_bytes(FILE* f, const char* filename);

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