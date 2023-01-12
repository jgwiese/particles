#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "renderbuffer.h"
#include "texture.h"


typedef struct {
    char *name;
    GLuint id;
    t_texture **a_texture;
    t_renderbuffer **a_renderbuffer;
    unsigned int a_texture_size;
    unsigned int a_renderbuffer_size;
} t_framebuffer;

t_framebuffer *framebuffer_new(char *name);
void framebuffer_init(t_framebuffer *p_framebuffer, char *name);
void framebuffer_check(t_framebuffer *p_framebuffer);
void framebuffer_attach_texture(t_framebuffer *p_framebuffer, t_texture *p_texture);
void framebuffer_attach_renderbuffer(t_framebuffer *p_framebuffer, t_renderbuffer *p_renderbuffer);
void framebuffer_use(t_framebuffer *p_framebuffer);
t_texture *framebuffer_get_color_attachement(t_framebuffer *p_framebuffer, unsigned int i);
void framebuffer_destroy(t_framebuffer *p_framebuffer);

#endif // FRAMEBuFFER_H

