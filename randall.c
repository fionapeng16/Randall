/* Generate N bytes of random output.  */

/* When generating output this program uses the x86-64 RDRAND
   instruction if available to generate random numbers, falling back
   on /dev/random and stdio otherwise.

   This program is not portable.  Compile it with gcc -mrdrnd for a
   x86-64 machine.

   Copyright 2015, 2017, 2020 Paul Eggert

   This program is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

//hearder libraries
#include <getopt.h>

//header files
#include "rand64-hw.h"
#include "rand64-sw.h"
#include "options.h"
#include "output.h"

/* Main program, which outputs N bytes of random data.  */
int main (int argc, char **argv)
{
    char *input = "rdrand";
    char *output = "stdio";

    int opt;
    while ((opt = getopt(argc, argv, "i:o:")) != -1) {
        switch (opt) {
            case 'i':
                input = optarg;
                break;
            case 'o':
                output = optarg;
                break;
            default: // '?' for unrecognized option
                fprintf(stderr, "Usage: %s [-i input] [-o output] NBYTES\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Expected argument after options\n");
        exit(EXIT_FAILURE);   
    }

    long long nbytes = handle_nbytes(argc, argv, optind);
    if (nbytes == 0)
        return 0;

    printf("Input: %s\nOutput: %s\n", input, output);

    void (*initialize)(void);
    unsigned long long (*rand64)(void);
    void (*finalize)(void);
    if (rdrand_supported()) {
        initialize = hardware_rand64_init;
        rand64 = hardware_rand64;
        finalize = hardware_rand64_fini;
    } else {
        initialize = software_rand64_init;
        rand64 = software_rand64;
        finalize = software_rand64_fini;
    }

    initialize();
    int result = handle_output(nbytes, rand64);
    finalize();

    if (result != 0) {
        perror("output");
        return result;
    }

    return 0;
}
