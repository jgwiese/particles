#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include "gl.h"


typedef struct {
    GLuint id;
} t_renderbuffer;

t_renderbuffer *renderbuffer_new(int width, int height);
void renderbuffer_init(t_renderbuffer *p_renderbuffer, int width, int height);
void renderbuffer_destroy(t_renderbuffer *p_renderbuffer);

#endif /*RENDERBUFFER_H*/

