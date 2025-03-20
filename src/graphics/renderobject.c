#include "renderobject.h"
#include "vertex.h"
#include "gl.h"
#include <stdlib.h>
#include <string.h>


t_renderobject *renderobject_new(t_mesh *p_mesh, unsigned int a_offsets_size) {
    t_renderobject *p_renderobject = calloc(1, sizeof(t_renderobject));
    renderobject_init(p_renderobject, p_mesh, a_offsets_size);
    return p_renderobject;
}

void renderobject_init(t_renderobject *p_renderobject, t_mesh *p_mesh, unsigned int a_offsets_size) {
    p_renderobject->p_mesh = p_mesh;
    p_renderobject->a_offsets = calloc(a_offsets_size, sizeof(glmc_vec3));
    p_renderobject->a_offsets_size = a_offsets_size;

    // Generate buffers
    glGenVertexArrays(1, &p_renderobject->vao);
    glGenBuffers(1, &p_renderobject->vbo);
    glGenBuffers(1, &p_renderobject->ibo);
    glGenBuffers(1, &p_renderobject->vbo_instances); // But not filled here.

    // Bind buffers and upload data
    glBindVertexArray(p_renderobject->vao);
    glBindBuffer(GL_ARRAY_BUFFER, p_renderobject->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(t_vertex) * p_renderobject->p_mesh->a_vertex_size, p_renderobject->p_mesh->a_vertex, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_renderobject->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * p_renderobject->p_mesh->a_indices_size, p_renderobject->p_mesh->a_indices, GL_STATIC_DRAW);

    // Configure vertex attribute pointers
    glEnableVertexAttribArray(0); // TODO: 0, 1, 2 are kind of fixed assumptions for position, normal, uv... unified way?
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *) 0); // NULL?
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *) (6 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, p_renderobject->vbo_instances);
    glBufferData(GL_ARRAY_BUFFER, p_renderobject->a_offsets_size * sizeof(glmc_vec3), p_renderobject->a_offsets, GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *) 0);
    glVertexAttribDivisor(3, 1);

    glBindVertexArray(0);
}

void renderobject_set_buffer(t_renderobject *p_renderobject, glmc_vec3 *a_offsets) {
    free(p_renderobject->a_offsets);
    p_renderobject->a_offsets = a_offsets;
    glBindBuffer(GL_ARRAY_BUFFER, p_renderobject->vbo_instances);
    glBufferData(GL_ARRAY_BUFFER, p_renderobject->a_offsets_size * sizeof(glmc_vec3), p_renderobject->a_offsets, GL_STATIC_DRAW);
}

void renderobject_draw(t_renderobject *p_renderobject, t_program *p_program) {
    glUseProgram(p_program->id);
    glBindVertexArray(p_renderobject->vao);
    glBindBuffer(GL_ARRAY_BUFFER, p_renderobject->vbo_instances);
    glDrawElementsInstanced(GL_TRIANGLES, p_renderobject->p_mesh->a_indices_size, GL_UNSIGNED_INT, 0, p_renderobject->a_offsets_size);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void renderobject_destroy(t_renderobject *p_renderobject) {
    //glDeleteBuffers(1, &p_renderobject->vbo_instances); // TODO why not working?
    //glDeleteBuffers(1, &p_renderobject->ibo);
    //glDeleteBuffers(1, &p_renderobject->vbo);
    //glDeleteVertexArrays(1, &p_renderobject->vao);
    mesh_destroy(p_renderobject->p_mesh);
    free(p_renderobject->a_offsets);
    free(p_renderobject);
}

