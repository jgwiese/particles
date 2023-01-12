#include "renderbuffer.h"
#include <stdlib.h>


t_renderbuffer *renderbuffer_new(int width, int height) {
    t_renderbuffer *p_renderbuffer = calloc(1, sizeof(t_renderbuffer));
    renderbuffer_init(p_renderbuffer, width, height);
    return p_renderbuffer;
}

void renderbuffer_init(t_renderbuffer *p_renderbuffer, int width, int height) {
    glGenRenderbuffers(1, &p_renderbuffer->id);
    glBindRenderbuffer(GL_RENDERBUFFER, p_renderbuffer->id);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}

void renderbuffer_destroy(t_renderbuffer *p_renderbuffer) {
    free(p_renderbuffer);
}

