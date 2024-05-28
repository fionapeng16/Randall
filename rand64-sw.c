#include "rand64-sw.h"

/* Software implementation.  */

/* Input stream containing random bytes.  */
FILE *urandstream;

void software_rand64_init_with_file(const char *file_path) {
    urandstream = fopen(file_path, "r");
    if (!urandstream) {
        perror("Failed to open random source file");
        abort();
    }
}

/* Initialize the software rand64 implementation.  */
void software_rand64_init (void)
{
  urandstream = fopen ("/dev/random", "r");
  if (! urandstream)
    abort ();
}

/* Return a random value, using software operations.  */
unsigned long long software_rand64 (void)
{
  unsigned long long int x;
  if (fread (&x, sizeof x, 1, urandstream) != 1)
    abort ();
  return x;
}

/* Finalize the software rand64 implementation.  */
void software_rand64_fini (void)
{
  fclose (urandstream);
}

struct drand48_data state;

void lrand48_init() {
    srand48_r(time(NULL), &state);
}

unsigned long long lrand48_rand64() {
    long int upper, lower;
    mrand48_r(&state, &upper); // first 32 bits
    mrand48_r(&state, &lower); // second 32 bits

    // shift the upper 32 bits left and merge with the lower 32 bits
    return ((uint64_t)upper << 32) | (uint32_t)lower;
}

void lrand48_fini() {
    // Cleanup if needed
}