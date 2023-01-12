#include "force_field.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


t_force_field *force_field_new() {
    t_force_field *p_force_field = calloc(1, sizeof(t_force_field));
    force_field_init(p_force_field);
    return p_force_field;
}

void force_field_init(t_force_field *p_force_field) {
    p_force_field->gravity_constant = 67430e-11;
    p_force_field->electric_constant = 8.8541878128e-12;
    p_force_field->boltzmann_constant = 1.380649e-23;
}

float force_field_gravity(t_force_field *p_force_field, float mass1, float mass2, float distance) {
    return p_force_field->gravity_constant * mass1 * mass2 / (distance * distance);
}

float force_field_custom(t_force_field *p_force_field, float q1, float q2, float distance) {
    return -log(distance/1.5) * 0.01;
}

void force_field_random_custom(t_force_field *p_force_field, glmc_vec3 *random_force) {
    glmc_vec3_init_random(random_force, -1.0, 1.0);
    glmc_vec3_divide(random_force, 1000.0, random_force);
}

void force_field_centering(t_force_field *p_force_field, glmc_vec3 *centering_force, glmc_vec3 *position) {
    glmc_vec3_add(centering_force, position, centering_force);
    glmc_vec3_divide(centering_force, -100.0, centering_force);
}

void force_field_destroy(t_force_field *p_force_field) {
    free(p_force_field);
}

