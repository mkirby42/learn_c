#include <stdio.h>      // For printf, fgets, etc.
#include <stdlib.h>     // For exit, malloc, etc.
#include <string.h>     // For strcmp, strtok, etc.
#include <dirent.h>     // For opendir, readdir, closedir
#include <sys/stat.h>   // For stat
#include <sys/types.h>  // For DIR*, struct stat
#include <unistd.h>     // For access, etc.
#include <limits.h>     // For PATH_MAX (if available on your system)

// Recursive function to walk the directory tree
void walker(const char *path, const char *findme)
{
    DIR *dir;
    struct dirent *entry;

    // Attempt to open the directory
    dir = opendir(path);
    if (!dir) {
        // Could not open directory
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Skip the "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct the full path to this entry
        char fullpath[PATH_MAX];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        // Use stat() to figure out if this is a directory or file
        struct stat st;
        if (stat(fullpath, &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                // It's a directory; recurse into it
                walker(fullpath, findme);
            } else {
                // It's a file; check if it matches 'findme'
                if (strcmp(entry->d_name, findme) == 0) {
                    printf("Found in: %s\n", path);
                }
            }
        }
    }

    closedir(dir);
}

int main(void)
{
    char buf[BUFSIZ];

    printf("This program will find a file on the current drive.\n");
    printf("Enter the name of the file to look for: ");
    fflush(stdout);

    if (fgets(buf, sizeof(buf), stdin) != NULL) {
        // Remove trailing newline
        buf[strcspn(buf, "\n")] = '\0';

        // Start at the current directory (".") or root ("/")
        walker(".", buf);
    }

    return 0;
}
