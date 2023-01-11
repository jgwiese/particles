#ifndef RENDERER_H
#define RENDERER_H

#include "framebuffer.h"
#include "canvas.h"
#include "resource_manager.h"
#include "../physics/particle_system.h"


typedef struct {
    unsigned int first_run;
    unsigned int a_framebuffer_size;
    t_framebuffer **a_framebuffer;
    t_canvas *p_canvas;
    t_resource_manager *p_resource_manager;
} t_renderer;

t_renderer *renderer_new();
void renderer_init(t_renderer *p_renderer);
void renderer_render(t_renderer *p_renderer, t_particle_system *p_particle_system);
void renderer_add_framebuffer(t_renderer *p_renderer, t_framebuffer *p_framebuffer);
t_framebuffer *renderer_get_framebuffer(t_renderer *p_renderer, char *name);

#endif // RENDERER_H

