#ifndef APPLICATION_H
#define APPLICATION_H

#include <time.h>
#include "graphics/glfw_window.h"
#include "graphics/renderer.h"
#include "physics/particle_system.h"


typedef struct {
    t_glfw_window *p_window;
    t_particle_system *p_particle_system;
    t_renderer *p_renderer;
    clock_t current_time;
    clock_t last_time;
    float time_step;
} t_application;

t_application *application_new(char *name);
void application_init(t_application *p_application, char *name);
void application_run(t_application *p_application);
void application_update(t_application *p_application);
void application_destroy(t_application *p_application);

#endif // APPLICATION_H
