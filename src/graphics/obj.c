#include "obj.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void *_parse_ints(char *str, size_t size) {
    int *buffer = calloc(size, sizeof(int));
    char *token;
    for (int i = 0; i < size; i++) {
        token = strsep(&str, " \n/");
        buffer[i] = atoi(token);
    }
    return (void *) buffer;
}

void *_parse_floats(char *str, size_t size) {
    float *buffer = calloc(size, sizeof(float));
    char *token;
    for (int i = 0; i < size; i++) {
        token = strsep(&str, " \n/");
        buffer[i] = atof(token);
    }
    return (void *) buffer;
}

void *_parse_line(char *line, enum obj_line_type *type) {
    char *line_copy = line;
    char *token = NULL;
    void *buffer = NULL;
    if (line_copy != NULL) {
        token = strsep(&line_copy, " \n");
        if (strcmp(token, "o") == 0) {
            *type = NAME;
            token = strsep(&line_copy, " \n");
            buffer = calloc(strlen(token), sizeof(char));
            strcpy(buffer, token);
        }
        else if (strcmp(token, "v") == 0) {
            *type = COORDINATES;
            buffer = _parse_floats(line_copy, 3);
        }
        else if (strcmp(token, "vn") == 0) {
            *type = NORMAL;
            buffer = _parse_floats(line_copy, 3);
        }
        else if (strcmp(token, "vt") == 0) {
            *type = UV;
            buffer = _parse_floats(line_copy, 2);
        }
        else if (strcmp(token, "mtllib") == 0) {
            *type = MATERIAL;
            token = strsep(&line_copy, " \n");
            buffer = calloc(strlen(token) + 1, sizeof(char));
            strcpy(buffer, token);
        }
        else if (strcmp(token, "f") == 0) {
            *type = FACE;
            buffer = _parse_ints(line_copy, 9);
        }
    }
    return buffer;
}

void face_indices_init_face_indices(t_face_indices *p_face_indices_target, t_face_indices *p_face_indices_source) {
    glmc_ivec3_init_ivec3(&p_face_indices_target->v1_indices, &p_face_indices_source->v1_indices);
    glmc_ivec3_init_ivec3(&p_face_indices_target->v2_indices, &p_face_indices_source->v2_indices);
    glmc_ivec3_init_ivec3(&p_face_indices_target->v3_indices, &p_face_indices_source->v3_indices);
}

t_obj *obj_new(char *path) {
    FILE *f;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    enum obj_line_type type;
    t_obj *p_obj = calloc(1, sizeof(t_obj));

    // Initialize obj struct
    p_obj->a_coordinates_size = 0;
    p_obj->a_normals_size = 0;
    p_obj->a_uvs_size = 0;
    p_obj->a_face_indices_size = 0;
    p_obj->a_coordinates = calloc(p_obj->a_coordinates_size, sizeof(glmc_vec3));
    p_obj->a_normals = calloc(p_obj->a_normals_size, sizeof(glmc_vec3));
    p_obj->a_uvs = calloc(p_obj->a_uvs_size, sizeof(glmc_vec2));
    p_obj->a_face_indices = calloc(p_obj->a_face_indices_size, sizeof(t_face_indices));

    f = fopen(path, "r");
    if (f == NULL) {
        printf("Error: File not found: %s\n", path);
    }

    void *buffer = NULL;
    while ((read = getline(&line, &len, f)) != -1) {
        type = NONE;
        buffer = _parse_line(line, &type);
        if (type == NAME) {
            p_obj->name = (char *) buffer;
        }
        if (type == COORDINATES) {
            p_obj->a_coordinates = realloc(p_obj->a_coordinates, (p_obj->a_coordinates_size + 1) * sizeof(glmc_vec3));
            glmc_vec3_init_vec3(&p_obj->a_coordinates[p_obj->a_coordinates_size], (glmc_vec3 *) buffer);
            p_obj->a_coordinates_size += 1;
        }
        if (type == NORMAL) {
            p_obj->a_normals = realloc(p_obj->a_normals, (p_obj->a_normals_size + 1) * sizeof(glmc_vec3));
            glmc_vec3_init_vec3(&p_obj->a_normals[p_obj->a_normals_size], (glmc_vec3 *) buffer);
            p_obj->a_normals_size += 1;
        }
        if (type == UV) {
            p_obj->a_uvs = realloc(p_obj->a_uvs, (p_obj->a_uvs_size + 1) * sizeof(glmc_vec2));
            glmc_vec2_init_vec2(&p_obj->a_uvs[p_obj->a_uvs_size], (glmc_vec2 *) buffer);
            p_obj->a_uvs_size += 1;
        }
        if (type == FACE) {
            p_obj->a_face_indices = realloc(p_obj->a_face_indices, (p_obj->a_face_indices_size + 1) * sizeof(t_face_indices));
            face_indices_init_face_indices(&p_obj->a_face_indices[p_obj->a_face_indices_size], (t_face_indices *) buffer);
            p_obj->a_face_indices_size += 1;
        }
        if (type ==  MATERIAL) {
            p_obj->material = (char *) buffer;
        }
    }

    fclose(f);
    if (line)
        free(line);
    return p_obj;
}

void obj_deallocate(t_obj *p_obj) {
    free(p_obj->a_coordinates);
    free(p_obj->a_normals);
    free(p_obj->a_uvs);
    free(p_obj->a_face_indices);
    free(p_obj->name);
    free(p_obj->material);
}

void obj_print(t_obj *p_obj) {
    printf("obj name: %s\n", p_obj->name);
    printf("material: %s\n", p_obj->material);
    printf("positions_size: %ld\n", p_obj->a_coordinates_size);
    printf("normal_size: %ld\n", p_obj->a_normals_size);
    printf("a_uvs_size: %ld\n", p_obj->a_uvs_size);
    printf("a_face_indices_size: %ld\n", p_obj->a_face_indices_size);
    for (unsigned int i = 0; i < p_obj->a_coordinates_size; i++) {
        glmc_vec3_print(&p_obj->a_coordinates[i]);
    }
    for (unsigned int i = 0; i < p_obj->a_normals_size; i++) {
        glmc_vec3_print(&p_obj->a_normals[i]);
    }
    for (unsigned int i = 0; i < p_obj->a_uvs_size; i++) {
        glmc_vec2_print(&p_obj->a_uvs[i]);
    }
    for (unsigned int i = 0; i < p_obj->a_face_indices_size; i++) {
        for (unsigned j = 0; j < 3; j++) {
            glmc_ivec3_print(&p_obj->a_face_indices[i].front[j]);
        }
    }
}

