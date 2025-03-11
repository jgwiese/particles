#ifndef CAMERA_H 
#define CAMERA_H 

#include <glmc/glmc.h>

static const float IDENTITY4[4][4] = {
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0, 1.0}
};

typedef struct {
    t_vec3 position;
    t_vec3 up;
    t_mat4 intrinsics;
    t_mat4 extrinsics;
} t_camera;

t_camera *camera_new();
void camera_init(t_camera *p_camera);

#endif // CAMERA_H
