#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <glmc/glmc.h>
#include "particle.h"
#include "force_field.h"
#include "../graphics/program.h"
#include "../graphics/mesh.h"
#include "../graphics/renderobject.h"


typedef struct {
    t_renderobject *p_renderobject;
    t_force_field *p_force_field;
    particle *a_particles;
    unsigned int a_particles_size;
} t_particle_system;

t_particle_system *particle_system_new(unsigned int a_particles_size);
void particle_system_init(t_particle_system *p_particle_system, unsigned int a_particles_size);
glmc_vec3 *particle_system_get_positions(t_particle_system *p_particle_system);
void particle_system_randomize_positions(t_particle_system *p_particle_system);
void particle_system_apply_force_field(t_particle_system *p_particle_system, t_force_field *p_force_field, float time_step);
void particle_system_update(t_particle_system *p_particle_system, float time_step);
void particle_system_draw(t_particle_system *p_particle_system, t_program *p_program);
void particle_system_destroy(t_particle_system *p_particle_system);

#endif // PARTICLE_SYSTEM_H

