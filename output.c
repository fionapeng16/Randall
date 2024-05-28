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

int handle_output(char *input, char *output, long long nbytes) {
   // Initialize local variables
   void (*initialize)(void);
   unsigned long long (*rand64)(void);
   void (*finalize)(void);

   // Error handling for missing input or output

   // Handle input options
   if (strcmp(input, "rdrand") == 0) {
        if (!rdrand_supported()) {
            fprintf(stderr, "RDRAND not supported on this hardware.\n");
            return 1;  // error code for unsupported hardware
        }
        // Handles hardware case
        initialize = hardware_rand64_init;
        rand64 = hardware_rand64;
        finalize = hardware_rand64_fini;
	
   } else if (strcmp(input, "lrand48_r") == 0) {
        // Handles lrand48_r case
        initialize = software_rand64_init;
        rand64 = software_rand64;         
        finalize = software_rand64_fini;
   } else {
        // Handle /F case.
        fprintf(stderr, "Unsupported input method: %s\n", input);
        return 1; // error code for unsupported input method
   }
   // Initialize random function
   initialize();
   unsigned long long rand_value;
   int output_errno = 0;

   if (strcmp(output, "stdio") == 0) {
        // Default stdio option
        while (nbytes > 0) {
            rand_value = rand64();
            int size_to_write = (long long int)sizeof(rand_value) > nbytes ? nbytes : (long long int)sizeof(rand_value);
            if (!writebytes(rand_value, size_to_write)) {
                fprintf(stderr, "Failed to write to stdout\n");
                output_errno = 1;
                break;
            }
            nbytes -= size_to_write;
        }
    } else {
        // Handle -o N option
        fprintf(stderr, "Unsupported output method: %s\n", output);
        output_errno = 1; 
   }

   finalize();
   return output_errno;
}
