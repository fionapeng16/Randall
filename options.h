#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

// function to handle command line arguments and return number of bytes.
long long handle_nbytes(int argc, char **argv, int index);

#endif // OPTIONS_H
