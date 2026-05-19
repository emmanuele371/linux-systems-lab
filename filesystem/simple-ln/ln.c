#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <errno.h>
#include <libgen.h>
#include <sys/stat.h>

static int verbose = 0;
static int symbolic = 0;

static void print_usage(const char *progname) {
    fprintf(stderr, "Usage: %s [-s] [-v] <source> <target>\n", progname);
    fprintf(stderr, "  -s    create symbolic link\n");
    fprintf(stderr, "  -v    verbose output\n");
}

/* Check whether target is a directory */
static int is_directory(const char *path) {
    struct stat sb;
    
    if (stat(path, &sb) == -1) {
        return 0;
    }
    
    return S_ISDIR(sb.st_mode);
}

int main(int argc, char *argv[]) {
    int opt;
    char *source, *target;
    char target_path[4096];
    int result;
    
    /* parse options */
    while ((opt = getopt(argc, argv, "sv")) != -1) {
        switch (opt) {
            case 's':
                symbolic = 1;
                break;
            case 'v':
                verbose = 1;
                break;
            default:
                print_usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    
    /* validate remaining arguments */
    if (argc - optind != 2) {
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    
    source = argv[optind];
    target = argv[optind + 1];
    
    /* if target is a directory, use basename(source) for the link name */
    if (is_directory(target)) {
        char *base = basename(source);
        snprintf(target_path, sizeof(target_path), "%s/%s", target, base);
        target = target_path;
    }
    
    /* create link */
    errno = 0;
    if (symbolic) {
        result = symlink(source, target);
    } else {
        result = link(source, target);
    }
    
    if (result == -1) {
        perror(symbolic ? "symlink" : "link");
        exit(EXIT_FAILURE);
    }
    
    /* verbose output */
    if (verbose) {
        if (symbolic) {
            printf("'%s' -> '%s' (symbolic link)\n", target, source);
        } else {
            printf("'%s' => '%s' (hard link)\n", target, source);
        }
    }
    
    return EXIT_SUCCESS;
}
