#include "options.h"

long long handle_nbytes(int argc, char **argv) {
    bool valid = false;
    long long nbytes = 0;
    if (argc == 2) {
        char *endptr;
        errno = 0;
        nbytes = strtoll(argv[1], &endptr, 10);
        if (errno)
            perror(argv[1]);
        else
            valid = !*endptr && 0 <= nbytes;
    }
    if (!valid) {
        fprintf(stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
        exit(EXIT_FAILURE);
    }
    return nbytes;
}
