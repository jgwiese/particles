#ifndef VERTEX_H
#define VERTEX_H

#include <glmc/glmc.h>


typedef struct {
    glmc_vec3 coordinates;
    glmc_vec3 normal;
    glmc_vec2 uv;
} t_vertex;

t_vertex *vertex_new(glmc_vec3 *coordinates, glmc_vec3 *normal, glmc_vec2 *uv);
void vertex_init(t_vertex *p_vertex, glmc_vec3 *coordinates, glmc_vec3 *normal, glmc_vec2 *uv);

#endif // VERTEX_H

