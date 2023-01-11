#ifndef MESH_H
#define MESH_H

#include "obj.h"
#include "vertex.h"
#include "face.h"


typedef struct {
    t_obj *p_obj;
    t_vertex *a_vertex; // TODO: use a_vertex to indicate that this is an array.
    t_face *a_face;
    unsigned int *a_indices; // is this necessary or could I use faces somehow?
    char *material;
    char *name;

    unsigned int a_vertex_size;
    unsigned int a_face_size;
    unsigned int a_indices_size;
} t_mesh;

void _copy_floats(float *arr1, float *arr2, size_t n);
void _create_mesh_from_obj(t_mesh *p_inst_mesh, t_obj *p_inst_obj);
t_mesh *mesh_new(char *path);
void mesh_init(t_mesh *p_mesh, char *path);
void mesh_print(t_mesh *p_inst_mesh);

#endif // MESH_H

