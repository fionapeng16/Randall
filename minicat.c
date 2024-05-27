#include <fcntl.h>
#include <unistd.h>

#define BUF_SZ 4096

intt main(int argc, char *argv[]) {
    int opt;
    int verbose = 0;
    while ((opt = getopt(arg, argv, "ve:")) != -1){
        switch (opt) {
            case 'v':
                verbose = 1;
                break;
            case 'e':
                printf("%s\n", optarg);
                break;
            default:
                fprintf(stderr, "Not a supported option: %c", opt);
                return 1;
        }
    }

    if (verbose) {
        printf("Verbose activated!\n");
    }

    // char filepath[] = "exampel.txt";

    char *filepath = argv[optind];

    // O_RDONLY opens a file readonly, as opposed to O_WRONLY for writeonly or O_RDWR for read/write
    int fd = open(filepath, O_RDONLY); // open file with intent to only read file
    if(fd < 0) 
        return 1; // if function returns less than 0 -> function FAILED!

    char buf[BUF_SZ];
    read(fd, buf, BUF_SZ);
    // STDOUT_FILENO is aliased to 1 on LIinux
    int n = write(STDOUT_FILENO, buf, BUF_SZ);
    if(n < 0)
        return 1;
    if(close(fd)<0)
        return 1; // close function can also fail!
    return 0;
}