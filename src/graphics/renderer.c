#include "renderer.h"
#include <stdlib.h>
#include "canvas.h"
#include "framebuffer.h"
#include "resource_manager.h"
#include "shader.h"
#include "program.h"
#include "../io/file.h"
#include "../io/string_mod.h"


t_renderer *renderer_new() {
    t_renderer *p_renderer = calloc(1, sizeof(t_renderer));
    renderer_init(p_renderer);
    return p_renderer;
}
void renderer_init(t_renderer *p_renderer) {
    char *cwd = get_current_working_directory();
    char *shaders_path = strjoin(cwd, "/shaders");

    p_renderer->first_run = 1;
    p_renderer->a_framebuffer_size = 0;
    p_renderer->p_canvas = canvas_new();
    p_renderer->p_resource_manager = resource_manager_new();

    // shaders
    resource_manager_add_shader(p_renderer->p_resource_manager, vertex_shader_new(strjoin(shaders_path, "/simple.vs"), "simple_vs"));
    resource_manager_add_shader(p_renderer->p_resource_manager, vertex_shader_new(strjoin(shaders_path, "/passthrough.vs"), "passthrough_vs"));

    resource_manager_add_shader(p_renderer->p_resource_manager, fragment_shader_new(strjoin(shaders_path, "/simple.fs"), "simple_fs"));
    resource_manager_add_shader(p_renderer->p_resource_manager, fragment_shader_new(strjoin(shaders_path, "/passthrough.fs"), "passthrough_fs"));
    resource_manager_add_shader(p_renderer->p_resource_manager, fragment_shader_new(strjoin(shaders_path, "/motion_blur.fs"), "motion_blur_fs"));
    resource_manager_add_shader(p_renderer->p_resource_manager, fragment_shader_new(strjoin(shaders_path, "/invert.fs"), "invert_fs"));

    // programs
    resource_manager_add_program(
        p_renderer->p_resource_manager,
        program_new(
            resource_manager_get_shader(p_renderer->p_resource_manager, "simple_vs"),
            resource_manager_get_shader(p_renderer->p_resource_manager, "simple_fs"),
            "simple_program"
        )
    );
    resource_manager_add_program(
        p_renderer->p_resource_manager,
        program_new(
            resource_manager_get_shader(p_renderer->p_resource_manager, "passthrough_vs"),
            resource_manager_get_shader(p_renderer->p_resource_manager, "passthrough_fs"),
            "passthrough_program"
        )
    );
    resource_manager_add_program(
        p_renderer->p_resource_manager,
        program_new(
            resource_manager_get_shader(p_renderer->p_resource_manager, "passthrough_vs"),
            resource_manager_get_shader(p_renderer->p_resource_manager, "motion_blur_fs"),
            "motion_blur_program"
        )
    );
    resource_manager_add_program(
        p_renderer->p_resource_manager,
        program_new(
            resource_manager_get_shader(p_renderer->p_resource_manager, "passthrough_vs"),
            resource_manager_get_shader(p_renderer->p_resource_manager, "invert_fs"),
            "invert_program"
        )
    );

    // textures
    resource_manager_add_texture(p_renderer->p_resource_manager, texture_new(1024, 1024, "target_00", NULL));
    resource_manager_add_texture(p_renderer->p_resource_manager, texture_new(1024, 1024, "target_01", NULL));
    resource_manager_add_texture(p_renderer->p_resource_manager, texture_new(1024, 1024, "target_02", NULL));
    resource_manager_add_texture(p_renderer->p_resource_manager, texture_new(1024, 1024, "target_03", NULL));

    // construct framebuffer
    renderer_add_framebuffer(p_renderer, framebuffer_new("previous"));
    framebuffer_attach_texture(
        renderer_get_framebuffer(p_renderer, "previous"), // TODO does it make sense to also manage framebuffers as a resource?
        resource_manager_get_texture(p_renderer->p_resource_manager, "target_00")
    );
    framebuffer_check(renderer_get_framebuffer(p_renderer, "previous"));

    renderer_add_framebuffer(p_renderer, framebuffer_new("scene"));
    framebuffer_attach_texture(
        renderer_get_framebuffer(p_renderer, "scene"),
        resource_manager_get_texture(p_renderer->p_resource_manager, "target_01")
    );
    framebuffer_check(renderer_get_framebuffer(p_renderer, "scene"));

    renderer_add_framebuffer(p_renderer, framebuffer_new("invert"));
    framebuffer_attach_texture(
        renderer_get_framebuffer(p_renderer, "invert"),
        resource_manager_get_texture(p_renderer->p_resource_manager, "target_02")
    );
    framebuffer_check(renderer_get_framebuffer(p_renderer, "invert"));

    renderer_add_framebuffer(p_renderer, framebuffer_new("motion_blur"));
    framebuffer_attach_texture(
        renderer_get_framebuffer(p_renderer, "motion_blur"),
        resource_manager_get_texture(p_renderer->p_resource_manager, "target_03")
    );
    framebuffer_check(renderer_get_framebuffer(p_renderer, "motion_blur"));
}

void renderer_render(t_renderer *p_renderer, t_particle_system *p_particle_system) {
    t_program *p_program;

    if (p_renderer->first_run) {
        // render offscreen
        framebuffer_use(renderer_get_framebuffer(p_renderer, "scene"));
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        particle_system_draw(p_particle_system, resource_manager_get_program(p_renderer->p_resource_manager, "simple_program"));

        // fake compose of the same scene
        framebuffer_use(renderer_get_framebuffer(p_renderer, "motion_blur"));
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        p_program = resource_manager_get_program(p_renderer->p_resource_manager, "motion_blur_program");
        glUseProgram(p_program->id);
        glUniform1i(glGetUniformLocation(p_program->id, "texture_00"), 0);
        glUniform1i(glGetUniformLocation(p_program->id, "texture_01"), 1);
        glActiveTexture(GL_TEXTURE0);
        texture_use(framebuffer_get_color_attachement(renderer_get_framebuffer(p_renderer, "scene"), 0));
        glActiveTexture(GL_TEXTURE1);
        texture_use(framebuffer_get_color_attachement(renderer_get_framebuffer(p_renderer, "scene"), 0));
        glUseProgram(0);
        canvas_draw(p_renderer->p_canvas, resource_manager_get_program(p_renderer->p_resource_manager, "motion_blur_program"));
        p_renderer->first_run = 0;
    }
    else {
        // save previous render
        framebuffer_use(renderer_get_framebuffer(p_renderer, "previous"));
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        p_program = resource_manager_get_program(p_renderer->p_resource_manager, "passthrough_program");
        glUseProgram(p_program->id);
        glUniform1i(glGetUniformLocation(p_program->id, "texture_00"), 0);
        glActiveTexture(GL_TEXTURE0);
        texture_use(framebuffer_get_color_attachement(renderer_get_framebuffer(p_renderer, "motion_blur"), 0));
        glUseProgram(0);
        canvas_draw(p_renderer->p_canvas, resource_manager_get_program(p_renderer->p_resource_manager, "passthrough_program"));

        // draw new scene
        framebuffer_use(renderer_get_framebuffer(p_renderer, "scene"));
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        particle_system_draw(p_particle_system, resource_manager_get_program(p_renderer->p_resource_manager, "simple_program"));
        
        // compose previous and current rendered scene
        framebuffer_use(renderer_get_framebuffer(p_renderer, "motion_blur"));
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        p_program = resource_manager_get_program(p_renderer->p_resource_manager, "motion_blur_program");
        glUseProgram(p_program->id);
        glUniform1i(glGetUniformLocation(p_program->id, "texture_00"), 0);
        glUniform1i(glGetUniformLocation(p_program->id, "texture_01"), 1);
        glActiveTexture(GL_TEXTURE0);
        texture_use(framebuffer_get_color_attachement(renderer_get_framebuffer(p_renderer, "previous"), 0));
        glActiveTexture(GL_TEXTURE1);
        texture_use(framebuffer_get_color_attachement(renderer_get_framebuffer(p_renderer, "scene"), 0));
        glUseProgram(0);
        canvas_draw(p_renderer->p_canvas, resource_manager_get_program(p_renderer->p_resource_manager, "motion_blur_program"));

        // invert colors
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        p_program = resource_manager_get_program(p_renderer->p_resource_manager, "invert_program");
        glUseProgram(p_program->id);
        glUniform1i(glGetUniformLocation(p_program->id, "texture_00"), 0);
        glActiveTexture(GL_TEXTURE0);
        texture_use(framebuffer_get_color_attachement(renderer_get_framebuffer(p_renderer, "motion_blur"), 0));
        canvas_draw(p_renderer->p_canvas, resource_manager_get_program(p_renderer->p_resource_manager, "invert_program"));
    }
}

void renderer_add_framebuffer(t_renderer *p_renderer, t_framebuffer *p_framebuffer) {
    unsigned int i = p_renderer->a_framebuffer_size;
    p_renderer->a_framebuffer = realloc(p_renderer->a_framebuffer, (i + 1) * sizeof(t_framebuffer *));
    p_renderer->a_framebuffer[i] = p_framebuffer;
    p_renderer->a_framebuffer_size += 1;
}

t_framebuffer *renderer_get_framebuffer(t_renderer *p_renderer, char *name) {
    for (unsigned int i = 0; i < p_renderer->a_framebuffer_size; i++) {
        if (p_renderer->a_framebuffer[i]->name == name) {
            return p_renderer->a_framebuffer[i];
        }
    }
    return NULL;
}

void renderer_destroy(t_renderer *p_renderer) {
    for (unsigned int i = 0; i < p_renderer->a_framebuffer_size; i++) {
        framebuffer_destroy(p_renderer->a_framebuffer[i]);
    }
    canvas_destroy(p_renderer->p_canvas);
    resource_manager_destroy(p_renderer->p_resource_manager);
    free(p_renderer);
}

