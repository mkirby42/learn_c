#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "dbg.h"

// Takes any sequence of words and finds all files that contain them all (assumed and condition)
// Optional argument of -o if we want this to be an 'or' instead
// Loads a list of allowed logfiles from ~/.logfind
// glob (lookup) 
// Output the lines as the scan progresses

void die(const char *message)
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

char *read_file_contents(char *file_path)
{
    char *source = NULL;
    FILE *fp = fopen(file_path, "r");
    if (fp != NULL) {
        // If we can put the position indicator at the end of the file (returns 0)
        if (fseek(fp, 0L, SEEK_END) == 0) {
            long buffsize = ftell(fp); // Get the position indicator value (at the end)
            if (buffsize == -1) {
                log_err("Unable to get to the end of file %s\n", file_path); 
                goto error;
            }

            // Allocate a buffer of that size
            source = malloc(sizeof(char) * (buffsize + 1));
            check_mem(source);

            // Try to put the position indicator back at the start of the file
            if (fseek(fp, 0L, SEEK_SET) != 0) {
                log_err("Unable to get back to the start of file %s\n", file_path);
                goto error;
            }

            // Read the file into memory
            size_t new_len = fread(source, sizeof(char), buffsize, fp);
            if (ferror(fp) != 0) {
                fputs("Error reading file", stderr);
            } else {
                source[new_len++] = '\0'; // Just to be safe
            }
        }
        fclose(fp);
    }

    return source;

error:
    if (fp) fclose(fp);
    source = NULL;
    fp = NULL;
    return NULL;
}

int main(int argc, char *argv[]) {
    // Take the words in argv and put them into char buffers
    check(argc >= 2, "Need an argument.");
    int count = argc - 1;
    int i = 0;
    for (i = 0; i <= count; i++) {
        // int string_size = strlen(argv[i]);
        printf("%s\n", argv[i]);
    }

    char *example_word_sequence = "respiration";
    printf("%s\n", example_word_sequence);

    char *file = read_file_contents("/Users/matt/.logfind/example_log_1.txt");
    printf("File contents: %s\n", file);

    // List of targets
    // List of false
    // Iterate through file contents
    // If word found change false to true for that word
    // Check all at each so only one pass is needed
    return 0;

error:
    example_word_sequence = NULL;
    return -1;
}