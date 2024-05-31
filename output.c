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

bool write_N_bytes(unsigned long long (*rand64)(void), int N, int nbytes){
    char *buffer = (char*) malloc(N);
    if (!buffer){
        perror("Memory allocation failed");
        return false;
    }

    long long total_written = 0;
    while (total_written < nbytes) {
        int bytes_to_write = N;
        if (nbytes - total_written < N)
            bytes_to_write = nbytes - total_written;

        for (int i = 0; i < bytes_to_write; i += sizeof(unsigned long long)) {
            if (i + (int)sizeof(unsigned long long) > bytes_to_write){
                unsigned long long rnd = rand64();
                memcpy(buffer + i, &rnd, bytes_to_write - i);
                break;
            } else {
                unsigned long long rnd = rand64();
                memcpy(buffer + i, &rnd, sizeof(unsigned long long));
            }
        }

        int written = write(STDOUT_FILENO, buffer, bytes_to_write);
        if (written < 0){
            perror("Error writing data");
            free(buffer);
            return false;
        }
        total_written += written;
    }
    free(buffer);
    return true;
}

int handle_output(char *input, char *output, long long nbytes) {
   // Initialize local variables
   void (*initialize)(void) = NULL;
   unsigned long long (*rand64)(void) = NULL;
   void (*finalize)(void) = NULL;

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
        initialize = lrand48_init;
        rand64 = lrand48_rand64;         
        finalize = lrand48_fini;
   } else if (strncmp(input, "/", 1) == 0) {  // Check if input starts with '/'
        // Handle /F case.
        set_global_file_path(input);
        initialize = software_rand64_init_with_file;
        rand64 = software_rand64;
        finalize = software_rand64_fini;
   } else {
        fprintf(stderr, "Unsupported input method: %s\n", input);
        return 1; // error code for unsupported input method
   }
   // Initialize random function
    if (initialize) {
        initialize();
    } else {
        fprintf(stderr, "Initialization function not set.\n");
        return 1;
    }
   unsigned long long rand_value;
   int output_errno = 0;
   char *endptr;
   long N = strtol(output, &endptr, 10);

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
    } else if (*endptr == '\0' && N > 0) {
        if (!write_N_bytes(rand64, N, nbytes)) {
            fprintf(stderr, "Failed to write bytes as expected\n");
            output_errno = 1;
        }
    } else {
        // Handle -o N option
        fprintf(stderr, "Unsupported output method: %s\n", output);
        output_errno = 1; 
   }

   finalize();
   return output_errno;
}
