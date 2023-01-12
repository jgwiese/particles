#ifndef PARTICLE_H
#define PARTICLE_H

#include <glmc/glmc.h>

typedef struct {
    glmc_vec3 position;
    glmc_vec3 velocity;
    glmc_vec3 acceleration;
    float mass;
    float radius;
} particle;

particle *particle_new(glmc_vec3 *position, float mass, float radius);
void particle_init(particle *p_particle, glmc_vec3 *position, float mass, float radius);
void particle_set_position(particle *p_particle, glmc_vec3 *position);
void particle_print(particle *p_particle);
void particle_destroy(particle *p_particle);

#endif // PARTICLE_H

