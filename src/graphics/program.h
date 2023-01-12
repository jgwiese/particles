#ifndef PROGRAM_H
#define PROGRAM_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"


typedef struct {
    char *name;
    GLuint id;
    t_shader *vertex_shader;
    t_shader *fragment_shader;
} t_program;

t_program *program_new(t_shader *p_shader_vertex, t_shader *p_shader_fragment, char *name);
void program_init(t_program *p_program, t_shader *p_shader_vertex, t_shader *p_shader_fragment, char *name);
void program_set_float(t_program *p_program, char *name, float value);
void program_destroy(t_program *p_program);

#endif // PROGRAM_H

