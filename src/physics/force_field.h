#ifndef FORCE_FIELD_H
#define FORCE_FIELD_H

#include <glmc/glmc.h>


// Force Field code
typedef struct {
    float gravity_constant;
    float electric_constant;
    float boltzmann_constant;
} t_force_field;

t_force_field *force_field_new();
void force_field_init(t_force_field *p_force_field);
float force_field_gravity(t_force_field *p_force_field, float mass1, float mass2, float distance);
float force_field_custom(t_force_field *p_force_field, float q1, float q2, float distance);
void force_field_random_custom(t_force_field *p_force_field, glmc_vec3 *random_force);
void force_field_centering(t_force_field *p_force_field, glmc_vec3 *centering_force, glmc_vec3 *position);
void force_field_destroy(t_force_field *p_force_field);

#endif // FORCE_FIELD_H

