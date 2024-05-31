#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "rand64-hw.h"
#include "rand64-sw.h"

// Function to output bytes.
bool writebytes(unsigned long long x, int nbytes);

// Function to handle the output process
int handle_output(char *input, char *output, long long nbytes);

#endif // OUTPUT_H