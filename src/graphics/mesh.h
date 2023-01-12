#ifndef MESH_H
#define MESH_H

#include "obj.h"
#include "vertex.h"
#include "face.h"


typedef struct {
    t_obj *p_obj;
    t_vertex *a_vertex;
    t_face *a_face;
    unsigned int *a_indices;
    char *material;
    char *name;
    unsigned int a_vertex_size;
    unsigned int a_face_size;
    unsigned int a_indices_size;
} t_mesh;

void _copy_floats(float *arr1, float *arr2, size_t n);
t_mesh *mesh_new(char *path);
void mesh_init(t_mesh *p_mesh, char *path);
void mesh_print(t_mesh *p_mesh);
void mesh_destroy(t_mesh *p_mesh);

#endif // MESH_H

