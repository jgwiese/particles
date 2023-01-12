#include "resource_manager.h"
#include <stdlib.h>
#include <stdio.h>


t_resource_manager *resource_manager_new() {
    t_resource_manager *p_resource_manager = calloc(1, sizeof(t_resource_manager));
    resource_manager_init(p_resource_manager);
    return p_resource_manager;
}

void resource_manager_init(t_resource_manager *p_resource_manager) {
    p_resource_manager->a_shader_size = 0;
    p_resource_manager->a_program_size = 0;
    p_resource_manager->a_texture_size = 0;
}

void resource_manager_add_shader(t_resource_manager *p_resource_manager, t_shader *p_shader) {
    unsigned int size = p_resource_manager->a_shader_size;
    p_resource_manager->a_shader = realloc(p_resource_manager->a_shader, (size + 1) * sizeof(t_shader *));
    p_resource_manager->a_shader[size] = p_shader;
    p_resource_manager->a_shader_size += 1;
    printf("added shader %s with gl id %d, now there are %d shaders\n", p_shader->name, p_shader->id, p_resource_manager->a_shader_size);
}

t_shader *resource_manager_get_shader(t_resource_manager *p_resource_manager, char *name) {
    for (unsigned int i = 0; i < p_resource_manager->a_shader_size; i++) {
        if (p_resource_manager->a_shader[i]->name == name) {
            return p_resource_manager->a_shader[i];
        }
    }
    return NULL;
}

void resource_manager_add_program(t_resource_manager *p_resource_manager, t_program *p_program) {
    unsigned int size = p_resource_manager->a_program_size;
    p_resource_manager->a_program = realloc(p_resource_manager->a_program, (size + 1) * sizeof(t_program *));
    p_resource_manager->a_program[size] = p_program;
    p_resource_manager->a_program_size += 1;
    printf("added program %s with gl id %d, now there are %d programs\n", p_program->name, p_program->id, p_resource_manager->a_program_size);
}

t_program *resource_manager_get_program(t_resource_manager *p_resource_manager, char *name) {
    for (unsigned int i = 0; i < p_resource_manager->a_program_size; i++) {
        if (p_resource_manager->a_program[i]->name == name) {
            return p_resource_manager->a_program[i];
        }
    }
    return NULL;
}

void resource_manager_add_texture(t_resource_manager *p_resource_manager, t_texture *p_texture) {
    unsigned int size = p_resource_manager->a_texture_size;
    p_resource_manager->a_texture = realloc(p_resource_manager->a_texture, (size + 1) * sizeof(t_texture *));
    p_resource_manager->a_texture[size] = p_texture;
    p_resource_manager->a_texture_size += 1;
    printf("added texture %s with gl id %d, now there are %d textures\n", p_texture->name, p_texture->id, p_resource_manager->a_texture_size);
}

t_texture *resource_manager_get_texture(t_resource_manager *p_resource_manager, char *name) {
    for (unsigned int i = 0; i < p_resource_manager->a_texture_size; i++) {
        if (p_resource_manager->a_texture[i]->name == name) {
            return p_resource_manager->a_texture[i];
        }
    }
    return NULL;
}

void resource_manager_destroy(t_resource_manager *p_resource_manager) {
    for (unsigned int i = 0; i < p_resource_manager->a_shader_size; i++) {
        shader_destroy(p_resource_manager->a_shader[i]);
    }
    for (unsigned int i = 0; i < p_resource_manager->a_program_size; i++) {
        program_destroy(p_resource_manager->a_program[i]);
    }
    for (unsigned int i = 0; i < p_resource_manager->a_texture_size; i++) {
        texture_destroy(p_resource_manager->a_texture[i]);
    }
    free(p_resource_manager);
}

