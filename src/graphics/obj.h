#ifndef OBJ_H
#define OBJ_H

#include <stddef.h>
#include <stdio.h>
#include <glmc/glmc.h>
#include "vertex.h"
#include "face.h"


enum obj_line_type {
    NONE,
    NAME,
    COORDINATES,
    NORMAL,
    UV,
    MATERIAL,
    FACE
};
typedef union {
    struct {
        glmc_ivec3 v1_indices;
        glmc_ivec3 v2_indices;
        glmc_ivec3 v3_indices;
    };
    glmc_ivec3 front[3];
} t_face_indices;

void face_indices_init_face_indices(t_face_indices *p_face_indices_target, t_face_indices *p_face_indices_source);
void face_indices_destroy(t_face_indices *p_face_indices);


typedef struct {
    glmc_vec3 *a_coordinates;
    glmc_vec3 *a_normals;
    glmc_vec2 *a_uvs;
    t_face_indices *a_face_indices;
    char *name;
    char *material;

    size_t a_coordinates_size;
    size_t a_normals_size;
    size_t a_uvs_size;
    size_t a_face_indices_size;
} t_obj;

void *_parse_ints(char *str, size_t size);
void *_parse_floats(char *str, size_t size);
void *_parse_line(char *line, enum obj_line_type *type);
t_obj *obj_new(char *path);
void obj_init(t_obj *p_obj, char *path);
void obj_print(t_obj *p_obj);
void obj_destroy(t_obj *p_obj);

#endif // OBJ_H

