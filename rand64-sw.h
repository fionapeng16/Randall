#ifndef RAND64_SW_H
#define RAND64_SW_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Input stream containing random bytes.  */
extern FILE *urandstream;

void software_rand64_init (void);

unsigned long long software_rand64 (void);

void software_rand64_fini (void);

#endif // RAND64_SW_H