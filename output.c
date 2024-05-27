#include "output.h"

bool writebytes(unsigned long long x, int nbytes) {
    do {
        if (putchar(x) < 0)
            return false;
        x >>= CHAR_BIT;
        nbytes--;
    } while (nbytes > 0);
    return true;
}

int handle_output(long long nbytes, unsigned long long (*rand64)(void)) {
    int wordsize = sizeof(unsigned long long);
    int output_errno = 0;

    do {
        unsigned long long x = rand64();
        int outbytes = nbytes < wordsize ? nbytes : wordsize;
        if (!writebytes(x, outbytes)) {
            output_errno = errno;
            break;
        }
        nbytes -= outbytes;
    } while (nbytes > 0);

    if (fclose(stdout) != 0)
        output_errno = errno;

    return output_errno ? !!output_errno : 0;
}