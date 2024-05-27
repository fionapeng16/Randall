#ifndef RAND64_HW_H
#define RAND64_HW_H

#include <stdbool.h>
#include <immintrin.h>
#include <cpuid.h>

_Bool
rdrand_supported (void);

void
hardware_rand64_init (void);

unsigned long long
hardware_rand64 (void);

void
hardware_rand64_fini (void);

#endif // RAND64_HW_H