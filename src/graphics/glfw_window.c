#include "glfw_window.h"
#include "../io/string_mod.h"
#include "../io/file.h"
#include "gl.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image/stb_image_write.h>
#include <stdio.h>
#include <stdlib.h>


void key_callback(GLFWwindow *p_window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(p_window, GLFW_TRUE);
    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        char *cwd = get_current_working_directory();
        int width, height;
        glfwGetWindowSize(p_window, &width, &height);
        unsigned char *data = calloc(4 * width * height, sizeof(unsigned char));
        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_write_png(strjoin(cwd, "/screenshot.png"), width, height, 4, data, 1024 * 4);
    }
}

t_glfw_window *glfw_window_new(int width, int height, char *name) {
    t_glfw_window *p_glfw_window = calloc(1, sizeof(t_glfw_window));

    if (!glfwInit()) {
        printf("glfw init failed.");
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    p_glfw_window->p_window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (!(p_glfw_window->p_window)) {
        printf("glfw window failed");
        return NULL;
    }
    glfwMakeContextCurrent(p_glfw_window->p_window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("Failed to initialize OpenGL context.\n");
        return NULL;
    }

    glfwSetKeyCallback(p_glfw_window->p_window, key_callback);
    p_glfw_window->running = 1;
    printf("%s, GLSL: %s\n", glGetString(GL_VERSION), glGetString (GL_SHADING_LANGUAGE_VERSION));
    return p_glfw_window;
}

void glfw_window_event(t_glfw_window *p_glfw_window) {
    glfwPollEvents();
    int return_value = glfwWindowShouldClose(p_glfw_window->p_window);
    if (return_value) {
        p_glfw_window->running = 0;
    }
}

void glfw_window_update(t_glfw_window *p_glfw_window) {
    glfwSwapBuffers(p_glfw_window->p_window);
}

void glfw_window_destroy(t_glfw_window *p_glfw_window) {
    glfwDestroyWindow(p_glfw_window->p_window);
    glfwTerminate();
    //free(p_glfw_window); // TODO why not working?
}

