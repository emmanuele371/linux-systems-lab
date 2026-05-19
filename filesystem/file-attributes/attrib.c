#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

/* Helper: return file type as a string */
static const char* get_file_type(mode_t mode) {
    if (S_ISREG(mode))  return "reguläre Datei";
    if (S_ISDIR(mode))  return "Verzeichnis";
    if (S_ISCHR(mode))  return "Zeichengerät";
    if (S_ISBLK(mode))  return "Blockgerät";
    if (S_ISFIFO(mode)) return "FIFO/Pipe";
    if (S_ISLNK(mode))  return "symbolischer Link";
    if (S_ISSOCK(mode)) return "Socket";
    return "unbekannt";
}

/* Helper: print permissions as a string (rwxrwxrwx) */
static void print_permissions(mode_t mode) {
    printf("Berechtigungen: ");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf(" (%04o)\n", mode & 07777);
}

/* Helper: print file attributes */
static void print_attributes(const char *filename, const struct stat *sb) {
    struct passwd *pw;
    struct group *gr;
    char timebuf[64];
    
    printf("Datei: %s\n", filename);
    printf("  Typ:            %s\n", get_file_type(sb->st_mode));
    printf("  Größe:          %ld Bytes\n", (long)sb->st_size);
    printf("  Blöcke:         %ld\n", (long)sb->st_blocks);
    printf("  Block-Größe:    %ld Bytes\n", (long)sb->st_blksize);
    printf("  Inode:          %ld\n", (long)sb->st_ino);
    printf("  Links:          %ld\n", (long)sb->st_nlink);
    printf("  ");
    print_permissions(sb->st_mode);
    
    /* owner */
    pw = getpwuid(sb->st_uid);
    if (pw != NULL) {
        printf("  Eigentümer:     %s (UID: %d)\n", pw->pw_name, sb->st_uid);
    } else {
        printf("  Eigentümer:     UID: %d\n", sb->st_uid);
    }
    
    /* group */
    gr = getgrgid(sb->st_gid);
    if (gr != NULL) {
        printf("  Gruppe:         %s (GID: %d)\n", gr->gr_name, sb->st_gid);
    } else {
        printf("  Gruppe:         GID: %d\n", sb->st_gid);
    }
    
    /* timestamps */
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", localtime(&sb->st_atime));
    printf("  Letzter Zugriff: %s\n", timebuf);
    
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", localtime(&sb->st_mtime));
    printf("  Letzte Änderung: %s\n", timebuf);
    
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", localtime(&sb->st_ctime));
    printf("  Letzte Statusänderung: %s\n", timebuf);
    
    printf("\n");
}

int main(int argc, char *argv[]) {
    int i;
    struct stat sb;
    int errors = 0;
    
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> [file2] [...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    /* process all provided files */
    for (i = 1; i < argc; i++) {
        errno = 0;
        if (lstat(argv[i], &sb) == -1) {
            fprintf(stderr, "%s: ", argv[i]);
            perror("lstat");
            errors++;
            continue;
        }
        
        print_attributes(argv[i], &sb);
    }
    
    return (errors > 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}
