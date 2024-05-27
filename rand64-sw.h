#ifndef RAND64_SW_H
#define RAND64_SW_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

/* Input stream containing random bytes.  */
extern FILE *urandstream;

void
software_rand64_init (void);

unsigned long long
software_rand64 (void);

void
software_rand64_fini (void);

bool
writebytes (unsigned long long x, int nbytes);

#endif // RAND64_SW_H