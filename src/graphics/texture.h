#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>


typedef struct {
    char *name;
    GLuint id;
    unsigned int width, height;
} t_texture;

t_texture *texture_new(unsigned int width, unsigned int height, char *name, unsigned char *data);
void texture_init(t_texture *p_texture, unsigned int width, unsigned int height, char *name, unsigned char *data);
void texture_use(t_texture *p_texture);

#endif // TEXTURE_H

