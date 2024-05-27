#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <stdbool.h>

// Function to output bytes.
bool writebytes(unsigned long long x, int nbytes);

// Function to handle the output process
int handle_output(long long nbytes, unsigned long long (*rand64)(void));

#endif // OUTPUT_H