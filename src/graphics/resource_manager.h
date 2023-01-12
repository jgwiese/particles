#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "shader.h"
#include "program.h"
#include "texture.h"


typedef struct {
    unsigned int a_shader_size;
    unsigned int a_program_size;
    unsigned int a_texture_size;
    t_shader **a_shader;
    t_program **a_program;
    t_texture **a_texture;
} t_resource_manager;

t_resource_manager *resource_manager_new();
void resource_manager_init(t_resource_manager *p_resource_manager);
void resource_manager_add_shader(t_resource_manager *p_resource_manager, t_shader *p_shader);
t_shader *resource_manager_get_shader(t_resource_manager *p_resource_manager, char *name);
void resource_manager_add_program(t_resource_manager *p_resource_manager, t_program *p_program);
t_program *resource_manager_get_program(t_resource_manager *p_resource_manager, char *name);
void resource_manager_add_texture(t_resource_manager *p_resource_manager, t_texture *p_texture);
t_texture *resource_manager_get_texture(t_resource_manager *p_resource_manager, char *name);
void resource_manager_destroy(t_resource_manager *p_resource_manager);

#endif // RESOURCE_MANAGER_H

