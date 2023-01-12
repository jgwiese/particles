#include "mesh.h"
#include "obj.h"
#include <glmc/vec2.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void _copy_floats(float *arr1, float *arr2, size_t n) {
    for (int i = 0; i < n; i++) {
        arr1[i] = arr2[i];
    }
}

t_mesh *mesh_new(char *path) {
    t_mesh *p_mesh = calloc(1, sizeof(t_mesh));
    mesh_init(p_mesh, path);
    return p_mesh;
}

void mesh_init(t_mesh *p_mesh, char *path) {
    p_mesh->p_obj = obj_new(path); // TODO later remove p_obj from attributes of p_mesh
    // Allocate memory
    p_mesh->a_vertex_size = p_mesh->p_obj->a_coordinates_size;
    p_mesh->a_face_size = p_mesh->p_obj->a_face_indices_size;
    p_mesh->a_indices_size = p_mesh->a_face_size * 3;

    p_mesh->a_vertex = calloc(p_mesh->a_vertex_size, sizeof(t_vertex));
    p_mesh->a_face = calloc(p_mesh->a_face_size, sizeof(t_face));
    p_mesh->a_indices = calloc(p_mesh->a_indices_size, sizeof(unsigned int));

    p_mesh->material = calloc(strlen(p_mesh->p_obj->material) + 1, sizeof(char));
    strcpy(p_mesh->material, p_mesh->p_obj->material);
    p_mesh->name = calloc(strlen(p_mesh->p_obj->name) + 1, sizeof(char));
    strcpy(p_mesh->name, p_mesh->p_obj->name);

    int coordinate_index, normal_index, uv_index;
    for (int i = 0; i < p_mesh->p_obj->a_face_indices_size; i++) {

        // for all three face indices save coordinates, normals and uvs in vertex structs.
        for (unsigned int j = 0; j < 3; j++) {
            coordinate_index = p_mesh->p_obj->a_face_indices[i].front[j].x - 1;
            uv_index = p_mesh->p_obj->a_face_indices[i].front[j].y - 1;
            normal_index = p_mesh->p_obj->a_face_indices[i].front[j].z - 1;
            glmc_vec3_init_vec3(&p_mesh->a_vertex[coordinate_index].coordinates, &p_mesh->p_obj->a_coordinates[coordinate_index]);
            glmc_vec3_init_vec3(&p_mesh->a_vertex[coordinate_index].normal, &p_mesh->p_obj->a_normals[normal_index]);
            glmc_vec2_init_vec2(&p_mesh->a_vertex[coordinate_index].uv, &p_mesh->p_obj->a_uvs[uv_index]);

            // flip y coordinates
            p_mesh->a_vertex[coordinate_index].uv.y = 1.0 - p_mesh->a_vertex[coordinate_index].uv.y;

            // fill face struct
            p_mesh->a_face[i].vertex_indices.front[j] = coordinate_index;
            for (unsigned int k = 0; k < 3; k++) {
                p_mesh->a_face[i].normal.front[k] += 1.0 / 3.0 * p_mesh->a_vertex[coordinate_index].normal.front[k];
            }
            p_mesh->a_indices[i * 3 + j] = coordinate_index;
        }
    }
}

void mesh_print(t_mesh *p_mesh) {
    printf("mesh name: %s\n", p_mesh->name);
    printf("material: %s\n", p_mesh->material);
    printf("a_vertex size: %u\n", p_mesh->a_vertex_size);
    printf("a_face size: %u\n", p_mesh->a_face_size);
    printf("a_indices size: %u\n", p_mesh->a_indices_size);
    for (unsigned int i = 0; i < p_mesh->a_vertex_size; i++) {
        glmc_vec3_print(&p_mesh->a_vertex[i].coordinates);
        glmc_vec3_print(&p_mesh->a_vertex[i].normal);
        glmc_vec2_print(&p_mesh->a_vertex[i].uv);
    }
    for (unsigned int i = 0; i < p_mesh->a_indices_size; i++) {
        printf("index: %d\n", p_mesh->a_indices[i]);
    }
}

void mesh_destroy(t_mesh *p_mesh) {
    printf("mesh destroy, %s\n", p_mesh->name);
    obj_destroy(p_mesh->p_obj);
    free(p_mesh->a_vertex);
    free(p_mesh->a_face);
    free(p_mesh->a_indices);
    free(p_mesh->material);
    free(p_mesh->name);
    free(p_mesh);
}

