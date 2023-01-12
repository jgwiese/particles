#include "texture.h"
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


t_texture *texture_new(unsigned int width, unsigned int height, char *name, unsigned char *data) {
    t_texture *p_texture = calloc(1, sizeof(t_texture));
    texture_init(p_texture, width, height, name, data);
    return p_texture;
}

void texture_init(t_texture *p_texture, unsigned int width, unsigned int height, char *name, unsigned char *data) {
    p_texture->width = width;
    p_texture->height = height;
    p_texture->name = calloc(strlen(name) + 1, sizeof(char));
    strcpy(p_texture->name, name);
    glGenTextures(1, &p_texture->id);
    glBindTexture(GL_TEXTURE_2D, p_texture->id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, p_texture->width, p_texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void texture_use(t_texture *p_texture) {
    glBindTexture(GL_TEXTURE_2D, p_texture->id);
}

void texture_destroy(t_texture *p_texture) {
    printf("texture destroy, name %s\n", p_texture->name);
    //glDeleteTextures(1, &p_texture->id);
    free(p_texture->name);
    free(p_texture);
}

