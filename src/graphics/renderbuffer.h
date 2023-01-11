#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>


typedef struct {
    GLuint id;
} t_renderbuffer;

t_renderbuffer *renderbuffer_new(int width, int height);
void renderbuffer_init(t_renderbuffer *p_renderbuffer, int width, int height);

#endif /*RENDERBUFFER_H*/

