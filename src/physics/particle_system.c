#include "particle_system.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../io/string_mod.h"
#include "../io/file.h"


t_particle_system *particle_system_new(unsigned int size) {
    t_particle_system *p_particle_system = calloc(1, sizeof(t_particle_system));
    particle_system_init(p_particle_system, size);
    return p_particle_system;
}

void particle_system_init(t_particle_system *p_particle_system, unsigned int size) {
    char *cwd = get_current_working_directory();
    char *meshes_path = strjoin(cwd, "/meshes");

    p_particle_system->force_field = force_field_new();
    p_particle_system->mesh = mesh_new(strjoin(meshes_path, "/sphere.obj"));
    p_particle_system->renderobject = renderobject_new(p_particle_system->mesh, size);
    p_particle_system->size = size;
    p_particle_system->particles = calloc(p_particle_system->size, sizeof(particle));
    particle_system_randomize_positions(p_particle_system);
}

glmc_vec3 *particle_system_get_positions(t_particle_system *p_particle_system) {
    glmc_vec3 *positions = calloc(p_particle_system->size, sizeof(glmc_vec3));
    for (unsigned int i = 0; i < p_particle_system->size; i++) {
        glmc_vec3_init_vec3(&positions[i], &p_particle_system->particles[i].position);
    }
    return positions;
}

void particle_system_randomize_positions(t_particle_system *p_particle_system) {
    glmc_vec3 random_position;
    for (unsigned int i = 0; i < p_particle_system->size; i++) {
        glmc_vec3_init_random(&random_position, -1.0, 1.0);
        particle_init(&p_particle_system->particles[i], &random_position, 1.0, 1.0);
    }
}

void particle_system_apply_force_field(t_particle_system *p_particle_system, force_field *force_field, float time_step) {
    particle *p1;
    particle *p2;
    glmc_vec3 gravity_force, random_force, centering_force;
    float distance, force;
    for (int i = 0; i < p_particle_system->size; i++) {
        p1 = &p_particle_system->particles[i];
        glmc_vec3_init(&p1->acceleration, 0.0, 0.0, 0.0);
        glmc_vec3_init(&random_force, 0.0, 0.0, 0.0);
        glmc_vec3_init(&centering_force, 0.0, 0.0, 0.0);
        //force_field_random_custom(force_field, &random_force);
        force_field_centering(force_field, &centering_force, &p1->position);
        force = 0.0;

        for (int j = 0; j < p_particle_system->size; j++) {
            if (i != j) {
                p2 = &p_particle_system->particles[j];
                // calculate gravity
                glmc_vec3_init(&gravity_force, 0.0, 0.0, 0.0);
                glmc_vec3_subtract(&p2->position, &p1->position, &gravity_force);
                distance = glmc_vec3_norm(&gravity_force);
                //force = force_field_gravity(force_field, p1->mass, p2->mass, distance);
                force = force_field_custom(force_field, p1->mass, p2->mass, distance);
               
                // now unit vector
                glmc_vec3_divide(&gravity_force, distance, &gravity_force);
                glmc_vec3_multiply(&gravity_force, force, &gravity_force);

                // apply gravity force
                glmc_vec3_add(&p1->acceleration, &gravity_force, &p1->acceleration);
                glmc_vec3_add(&p1->acceleration, &centering_force, &p1->acceleration);
            }
        }
        // update particle
        glmc_vec3_multiply(&p1->acceleration, time_step, &p1->acceleration);
        glmc_vec3_add(&p1->velocity, &p1->acceleration, &p1->velocity);
    }
    for (int i = 0; i < p_particle_system->size; i++) {
        p1 = &p_particle_system->particles[i];
        glmc_vec3_add(&p1->position, &p1->velocity, &p1->position);
    }
}

void particle_system_update(t_particle_system *p_particle_system, float time_step) {
    // update
    particle_system_apply_force_field(p_particle_system, p_particle_system->force_field, time_step);
}

void particle_system_draw(t_particle_system *p_particle_system, t_program *p_program) {
    glmc_vec3 *offsets;
    offsets = particle_system_get_positions(p_particle_system);
    renderobject_set_buffer(p_particle_system->renderobject, offsets);
    renderobject_draw(p_particle_system->renderobject, p_program);
}

