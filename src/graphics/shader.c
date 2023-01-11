#include "shader.h"
#include <stdio.h>
#include <stdlib.h>
#include "../io/file.h"


t_shader *shader_new(char *path, GLenum shader_type, char *name) {
    t_shader *p_shader = calloc(1, sizeof(t_shader));
    shader_init(p_shader, path, shader_type, name);
    return p_shader;
}

void shader_init(t_shader *p_shader, char *path, GLenum shader_type, char *name) {
    p_shader->name = name;
    char *buffer;
    if (parse_file(&buffer, path) == 1) {
        printf("shader file empty\n");
    }
    p_shader->id = glCreateShader(shader_type);
    glShaderSource(p_shader->id, 1, (const GLchar **) &buffer, NULL);
    glCompileShader(p_shader->id);
    
    GLint is_compiled = 0;
    glGetShaderiv(p_shader->id, GL_COMPILE_STATUS, &is_compiled);
    if (is_compiled == GL_FALSE) {
        GLint max_length = 0;
        glGetShaderiv(p_shader->id, GL_INFO_LOG_LENGTH, &max_length);
        GLchar message[max_length];
        glGetShaderInfoLog(p_shader->id, max_length, &max_length, message);
        printf("%s", message);
        glDeleteShader(p_shader->id);
    }
}

t_shader *vertex_shader_new(char *path, char *name) {
    return shader_new(path, GL_VERTEX_SHADER, name);
}

t_shader *fragment_shader_new(char *path, char *name) {
    return shader_new(path, GL_FRAGMENT_SHADER, name);
}

