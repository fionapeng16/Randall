#ifndef RAND64_SW_H
#define RAND64_SW_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <stdint.h>

/* Input stream containing random bytes.  */
extern FILE *urandstream;

void software_rand64_init (void);

unsigned long long software_rand64 (void);

void software_rand64_fini (void);

void lrand48_init();

unsigned long long lrand48_rand64();

void lrand48_fini();

void software_rand64_init_with_file(void);

void set_global_file_path(const char* file_path);

#endif // RAND64_SW_H