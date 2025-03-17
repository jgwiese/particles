#include "gl_debug.h"
#include "gl.h"
#include <stdio.h>


void print_glerror() {
    printf("gl error: %d\n", glGetError());
}

