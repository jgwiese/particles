#ifndef GLFW_WINDOW_H
#define GLFW_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>


typedef struct {
    GLFWwindow *p_window;
    int running;
} t_glfw_window;

void key_callback(GLFWwindow *p_window, int key, int scancode, int action, int mods);
t_glfw_window *glfw_window_new(int width, int height, char *name);
void glfw_window_event(t_glfw_window *p_glfw_window);
void glfw_window_update(t_glfw_window *p_glfw_window);
void glfw_window_destroy(t_glfw_window *p_glfw_window);

#endif // GLFW_WINDOW_H

