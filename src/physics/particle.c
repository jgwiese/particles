#include "particle.h"
#include <stdlib.h>


particle *particle_new(glmc_vec3 *position, float mass, float radius) {
    particle *p_particle = calloc(1, sizeof(particle));
    particle_init(p_particle, position, mass, radius);
    particle_set_position(p_particle, position);
    p_particle->mass = 1.0;
    p_particle->radius = 1.0;
    return p_particle;
}

void particle_init(particle *p_particle, glmc_vec3 *position, float mass, float radius) {
    particle_set_position(p_particle, position);
    glmc_vec3_init(&p_particle->velocity, 0.0, 0.0, 0.0);
    glmc_vec3_init(&p_particle->acceleration, 0.0, 0.0, 0.0);
    p_particle->mass = mass;
    p_particle->radius = radius;
}

void particle_set_position(particle *p_particle, glmc_vec3 *position) {
    p_particle->position.x = position->x;
    p_particle->position.y = position->y;
    p_particle->position.z = position->z;
}

void particle_print(particle *p_particle) {
    // for now only the position
    glmc_vec3_print(&p_particle->position);
}

void particle_destroy(particle *p_particle) {
    glmc_vec3_destroy(&p_particle->position);
    glmc_vec3_destroy(&p_particle->velocity);
    glmc_vec3_destroy(&p_particle->acceleration);
    free(p_particle);
}

