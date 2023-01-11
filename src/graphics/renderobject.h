#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glmc/glmc.h>
#include "mesh.h"
#include "program.h"


typedef struct {
    t_mesh *mesh;
    GLuint vao;
    GLuint vbo;
    GLuint ibo;
    GLuint vbo_instances;
    glmc_vec3 *a_offsets;
    unsigned int a_offsets_size;
} t_renderobject;

t_renderobject *renderobject_new(t_mesh *p_mesh, unsigned int a_offset_size);
void renderobject_init(t_renderobject *p_renderobject, t_mesh *p_mesh, unsigned int a_offset_size);
void renderobject_set_buffer(t_renderobject *p_renderobject, glmc_vec3 *a_offsets);
void renderobject_draw(t_renderobject *p_renderobject, t_program *p_program);

#endif // RENDEROBJECT_H

