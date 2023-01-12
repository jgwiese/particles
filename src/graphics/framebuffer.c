#include "framebuffer.h"
#include <stdlib.h>
#include <stdio.h>


t_framebuffer *framebuffer_new(char *name) {
    t_framebuffer *p_framebuffer = calloc(1, sizeof(t_framebuffer));
    framebuffer_init(p_framebuffer, name);
    return p_framebuffer;
}

void framebuffer_init(t_framebuffer *p_framebuffer, char *name) {
    p_framebuffer->name = name;
    glGenFramebuffers(1, &p_framebuffer->id);
    glBindFramebuffer(GL_FRAMEBUFFER, p_framebuffer->id);
    p_framebuffer->a_texture = calloc(16, sizeof(t_texture *));
    p_framebuffer->a_renderbuffer = calloc(16, sizeof(t_renderbuffer *));
    p_framebuffer->a_texture_size = 0;
    p_framebuffer->a_renderbuffer_size = 0;
}

void framebuffer_check(t_framebuffer *p_framebuffer) {
    glBindFramebuffer(GL_FRAMEBUFFER, p_framebuffer->id);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("error: framebuffer is not complete\n");
    else
        printf("success: framebuffer is complete\n");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void framebuffer_use(t_framebuffer *p_framebuffer) {
    glBindFramebuffer(GL_FRAMEBUFFER, p_framebuffer->id);
}

void framebuffer_attach_texture(t_framebuffer *p_framebuffer, t_texture *p_texture) {
    glBindFramebuffer(GL_FRAMEBUFFER, p_framebuffer->id);
    unsigned int i = p_framebuffer->a_texture_size;
    p_framebuffer->a_texture[i] = p_texture;
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, p_framebuffer->a_texture[i]->id, 0);
    p_framebuffer->a_texture_size += 1;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void framebuffer_attach_renderbuffer(t_framebuffer *p_framebuffer, t_renderbuffer *p_renderbuffer) {
    glBindFramebuffer(GL_FRAMEBUFFER, p_framebuffer->id);
    unsigned int i = p_framebuffer->a_renderbuffer_size;
    p_framebuffer->a_renderbuffer[i] = p_renderbuffer;
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, p_renderbuffer->id);
    p_framebuffer->a_renderbuffer_size += 1;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

t_texture *framebuffer_get_color_attachement(t_framebuffer *p_framebuffer, unsigned int i) {
    return p_framebuffer->a_texture[i];
}

void framebuffer_destroy(t_framebuffer *p_framebuffer) {
    for (unsigned int i = 0; i < p_framebuffer->a_texture_size; i++) {
        texture_destroy(p_framebuffer->a_texture[i]);
    }
    for (unsigned int i = 0; i < p_framebuffer->a_renderbuffer_size; i++) {
        renderbuffer_destroy(p_framebuffer->a_renderbuffer[i]);
    }
    free(p_framebuffer);
}

