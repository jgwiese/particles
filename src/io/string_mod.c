#include "string_mod.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>


char *strjoin(char *prefix, char *suffix) {
    char *path = calloc(PATH_MAX, sizeof(char));
    strcpy(path, prefix);
    strcat(path, suffix);
    return path;
}

