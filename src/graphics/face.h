#ifndef FACE_H
#define FACE_H

#include <glmc/glmc.h>


typedef struct {
    glmc_ivec3 vertex_indices;
    glmc_vec3 normal;
} t_face;

t_face *face_new(glmc_ivec3 *vertex_indices, glmc_vec3 *normal);
void face_init(t_face *p_face, glmc_ivec3 *vertex_indices, glmc_vec3 *normal);
void face_destroy(t_face *p_face);

#endif // FACE_H

