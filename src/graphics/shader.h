#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>


typedef struct {
    char *name;
    GLuint id;
    GLenum shader_type;
} t_shader;

t_shader *shader_new(char *path, GLenum shader_type, char *name);
void shader_init(t_shader *p_shader, char *path, GLenum shader_type, char *name);
t_shader *vertex_shader_new(char *path, char *name);
t_shader *fragment_shader_new(char *path, char *name);
void shader_destroy(t_shader *p_shader);

#endif // SHADER_H

