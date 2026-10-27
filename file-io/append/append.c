#include <unistd.h> // read, write, close
#include <fcntl.h> // open, O_RDONLY, etc
#include <stdlib.h> // EXIT_FAILURE, _SUCCESS
#include <sys/stat.h> // fstat, info on the file
#include <sys/types.h> // for umask flags
#include <errno.h> // read errors

#ifndef O_CLOEXEC
#define O_CLOEXEC 0
#endif

#define BUF_SIZE 4096

static size_t slen(const char *str)
{
	size_t l = 0;
	while (str[l]) l++;
 	return l;
}

static int write_all(int fd, const char *buf, size_t len)
{
    // write() may be partial, loop until all bytes are written
    	size_t off = 0;
    	while (off < len) {
        ssize_t n = write(fd, buf + off, len - off);
        if (n < 0) {
    // retry on signals or transient errors
            if (errno == EINTR) continue;
            return -1; // otherwise exit with -1
        }
        off += (size_t)n;
    }
    return 0;
}

static void ewrite_str(const char *str)
{
    // write to stderr without stdio
    (void)write_all(2, str, slen(str));
}

int main(int argc, char *argv[])
{
    // argv check
    if (argc != 3) {
        ewrite_str("Usage: append <src-file> <dst-file>\n");
        return EXIT_FAILURE;
    }

    // src: read only
    int fd_in = open(argv[1], O_RDONLY | O_CLOEXEC);
    if (fd_in < 0) {
        ewrite_str("append: cannot open src-file\n. Vielleicht existiert es nicht?");
        return EXIT_FAILURE;
    }

    // dst: write + create + append
    // 0666 -> umask applies the real permissions
    int fd_out = open(argv[2], O_WRONLY | O_CREAT | O_APPEND | O_CLOEXEC, 0666);
    if (fd_out < 0) {
        ewrite_str("append: cannot open dst-file\n");
        close(fd_in);
        return EXIT_FAILURE;
    }

    // avoid infinite append
    struct stat st_in;
    struct stat st_out;
    if (fstat(fd_in, &st_in) < 0 || fstat(fd_out, &st_out) < 0) {
        ewrite_str("append: fstat failed\n");
        close(fd_in);
        close(fd_out);
        return EXIT_FAILURE;
    }

    if (st_in.st_dev == st_out.st_dev && st_in.st_ino == st_out.st_ino) {
        ewrite_str("append: src and dst are the same file\n");
        close(fd_in);
        close(fd_out);
        return EXIT_FAILURE;
    }

    char buf[BUF_SIZE];
    for (;;) {
        // read loop until EOF
        ssize_t n = read(fd_in, buf, sizeof(buf));
        if (n == 0) break;
        if (n < 0) { 
            if (errno == EINTR) continue;
            ewrite_str("append: read failed\n");
            close(fd_in);
            close(fd_out);
            return EXIT_FAILURE;
        }

        // write all data (handle partial writes)
        if (write_all(fd_out, buf, (size_t)n) < 0) {
            ewrite_str("append: write failed\n");
            close(fd_in);
            close(fd_out);
            return EXIT_FAILURE;
        }
    }

    // clean up
    close(fd_in);
    close(fd_out);
    return EXIT_SUCCESS;
}
