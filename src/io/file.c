#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int parse_file(char **buffer, const char *path) {
    FILE *f;
    f = fopen(path, "rb");
    if (f == NULL) {
        printf("Error: File not found: %s\n", path);
        return 1;
    }
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    *buffer = malloc((fsize + 1) * sizeof(char));
    if (fread(*buffer, 1, fsize, f) == 0)
        printf("file empty.\n");
    fclose(f);
    (*buffer)[fsize] = '\0';
    return 0;
}

char *get_current_working_directory() {
    char *cwd = malloc(sizeof(char) * PATH_MAX);
    if (getcwd(cwd, sizeof(char) * PATH_MAX) != NULL) {
        return cwd;
    }
    else {
        perror("getcwd() error");
        return NULL;
    }
}

