#include "camera.h"
#include <stdlib.h>
#include <stdio.h>


t_camera *camera_new() {
    t_camera *p_camera = calloc(1, sizeof(t_camera));
    camera_init(p_camera);
    return p_camera;
}

void camera_init(t_camera *p_camera) {
    glmc_vec3_init(&p_camera->position, 0.0, 0.0, 0.0);
    glmc_vec3_init(&p_camera->up, 0.0, 1.0, 0.0);

    glmc_mat4_init(&p_camera->intrinsics, (float *) &IDENTITY4);
    glmc_mat4_init(&p_camera->extrinsics, (float *) &IDENTITY4);

    glmc_mat4_print(&p_camera->intrinsics);
}

void camera_destroy(t_camera *p_camera) {
    glmc_vec3_destroy(&p_camera->position);
    glmc_vec3_destroy(&p_camera->up);
    free(p_camera);
}
