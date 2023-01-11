#ifndef FORCE_FIELD_H
#define FORCE_FIELD_H

#include <glmc/glmc.h>


// Force Field code
typedef struct {
    float gravity_constant;
    float electric_constant;
    float boltzmann_constant;
} force_field;

force_field *force_field_new();
void force_field_init(force_field *p_force_field);
float force_field_gravity(force_field *force_field, float mass1, float mass2, float distance);
float force_field_custom(force_field *force_field, float q1, float q2, float distance);
void force_field_random_custom(force_field *force_field, glmc_vec3 *random_force);
void force_field_centering(force_field *force_field, glmc_vec3 *centering_force, glmc_vec3 *position);

#endif // FORCE_FIELD_H

