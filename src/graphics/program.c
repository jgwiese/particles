#include "program.h"
#include <stdlib.h>
#include <string.h>


t_program *program_new(t_shader *p_shader_vertex, t_shader *p_shader_fragment, char *name) {
    t_program *p_program = calloc(1, sizeof(t_program));
    program_init(p_program, p_shader_vertex, p_shader_fragment, name);
    return p_program;
}

void program_init(t_program *p_program, t_shader *p_shader_vertex, t_shader *p_shader_fragment, char *name) {
    p_program->name = calloc(strlen(name) + 1, sizeof(char));
    strcpy(p_program->name, name);
    p_program->id = glCreateProgram();
    glAttachShader(p_program->id, p_shader_vertex->id);
    glAttachShader(p_program->id, p_shader_fragment->id);
    glLinkProgram(p_program->id);
}

void program_set_float(t_program *p_program, char *name, float value) {
    glUseProgram(p_program->id);
    glUniform1f(glGetUniformLocation(p_program->id, name), value);
    glUseProgram(0);
}

void program_destroy(t_program *p_program) {
    free(p_program->name);
    free(p_program);
}

