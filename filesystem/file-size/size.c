#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

/* Convert bytes to a readable unit */
static void print_size(const char *label, off_t bytes) {
    double size = (double)bytes;
    
    if (bytes > 2048LL * 1024 * 1024) {
        /* GiB */
        size = bytes / (1024.0 * 1024.0 * 1024.0);
        printf("%s: %.2f GiB\n", label, size);
    } else if (bytes > 2048LL * 1024) {
        /* MiB */
        size = bytes / (1024.0 * 1024.0);
        printf("%s: %.2f MiB\n", label, size);
    } else if (bytes > 2048) {
        /* KiB */
        size = bytes / 1024.0;
        printf("%s: %.2f KiB\n", label, size);
    } else {
        /* Bytes */
        printf("%s: %ld Bytes\n", label, (long)bytes);
    }
}

int main(int argc, char *argv[]) {
    struct stat sb;
    off_t allocated_space;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    errno = 0;
    if (stat(argv[1], &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    
    /* file size */
    print_size("Dateigröße", sb.st_size);
    
    /* allocated space (blocks * 512 bytes) */
    allocated_space = sb.st_blocks * 512;
    print_size("Allokierter Speicherplatz", allocated_space);
    
    return EXIT_SUCCESS;
}
