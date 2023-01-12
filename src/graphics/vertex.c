#include "vertex.h"
#include <stdlib.h>
#include <string.h>


t_vertex *vertex_new(glmc_vec3 *coordinates, glmc_vec3 *normal, glmc_vec2 *uv) {
    t_vertex *p_vertex = calloc(1, sizeof(t_vertex));
    vertex_init(p_vertex, coordinates, normal, uv);
    return p_vertex;
}

void vertex_init(t_vertex *p_vertex, glmc_vec3 *coordinates, glmc_vec3 *normal, glmc_vec2 *uv) {
    glmc_vec3_init_vec3(&p_vertex->coordinates, coordinates);
    glmc_vec3_init_vec3(&p_vertex->normal, coordinates);
    glmc_vec2_init_vec2(&p_vertex->uv, uv);
}

void vertex_destroy(t_vertex *p_vertex) {
    glmc_vec3_destroy(&p_vertex->coordinates);
    glmc_vec3_destroy(&p_vertex->normal);
    glmc_vec2_destroy(&p_vertex->uv);
}

