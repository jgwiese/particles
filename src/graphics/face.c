#include "face.h"
#include <stdlib.h>
#include "vertex.h"


t_face *face_new(glmc_ivec3 *vertex_indices, glmc_vec3 *normal) {
    t_face *p_face = calloc(1, sizeof(t_face));
    face_init(p_face, vertex_indices, normal);
    return p_face;
}

void face_init(t_face *p_face, glmc_ivec3 *vertex_indices, glmc_vec3 *normal) {
    glmc_ivec3_init_ivec3(&p_face->vertex_indices, vertex_indices);
    glmc_vec3_init_vec3(&p_face->normal, normal);
}

void face_destroy(t_face *p_face) {
    glmc_ivec3_destroy(&p_face->vertex_indices);
    glmc_vec3_destroy(&p_face->normal);
    free(p_face);
}

