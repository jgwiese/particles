#include "gl_debug.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>


void print_glerror() {
    printf("gl error: %d\n", glGetError());
}

