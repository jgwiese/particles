#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <glmc/glmc.h>
#include "particle.h"
#include "force_field.h"
#include "../graphics/program.h"
#include "../graphics/mesh.h"
#include "../graphics/renderobject.h"


typedef struct {
    t_renderobject *renderobject;
    t_mesh *mesh;
    force_field *force_field;
    particle *particles;
    unsigned int size;
} t_particle_system;

t_particle_system *particle_system_new(unsigned int size);
void particle_system_init(t_particle_system *p_particle_system, unsigned int size);
glmc_vec3 *particle_system_get_positions(t_particle_system *particle_system);
void particle_system_randomize_positions(t_particle_system *particle_system);
void particle_system_apply_force_field(t_particle_system *particle_system, force_field *force_field, float time_step);
void particle_system_update(t_particle_system *p_particle_system, float time_step);
void particle_system_draw(t_particle_system *p_particle_system, t_program *p_program);

#endif // PARTICLE_SYSTEM_H
