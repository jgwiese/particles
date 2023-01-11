#include "application.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "physics/force_field.h"
#include "physics/particle_system.h"


t_application *application_new(char *name) {
    t_application *p_application = calloc(1, sizeof(t_application));
    application_init(p_application, name);
    return p_application;
}

void application_init(t_application *p_application, char *name) {
    p_application->p_window = glfw_window_new(1024, 1024, name);
    p_application->p_particle_system = particle_system_new(16);
    p_application->p_renderer = renderer_new();
    p_application->last_time = clock();
    p_application->current_time = clock();
    p_application->time_step = (float) (p_application->current_time - p_application->last_time);
}

void application_run(t_application *p_application) {
    // loop
    while (p_application->p_window->running) {
        glfw_window_event(p_application->p_window);
        application_update(p_application);
        glfw_window_update(p_application->p_window);
    }

    glfw_window_destroy(p_application->p_window);
}

void application_update(t_application *p_application) {
    // time step
    p_application->last_time = p_application->current_time;
    p_application->current_time = clock();
    p_application->time_step = (float) (p_application->current_time - p_application->last_time) / CLOCKS_PER_SEC;

    // particle system update
    particle_system_update(p_application->p_particle_system, p_application->time_step);
    renderer_render(p_application->p_renderer, p_application->p_particle_system);
}

