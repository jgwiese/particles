#include "canvas.h"
#include "shader.h"
#include "../io/string_mod.h"
#include "../io/file.h"
#include <glmc/glmc.h>
#include <stdlib.h>


t_canvas *canvas_new() {
    t_canvas *p_canvas = calloc(1, sizeof(t_canvas));
    canvas_init(p_canvas);
    return p_canvas;
}

void canvas_init(t_canvas *p_canvas) {
    char *cwd = get_current_working_directory();
    char *meshes_path = strjoin(cwd, "/meshes");

    t_mesh *p_mesh = mesh_new(strjoin(meshes_path, "/quad.obj"));
    p_canvas->p_renderobject = renderobject_new(p_mesh, 1);
}

void canvas_draw(t_canvas *p_canvas, t_program *p_program) {
    glmc_vec3 *offsets = glmc_vec3_new(0.0, 0.0, 0.0);
    renderobject_set_buffer(p_canvas->p_renderobject, offsets);
    renderobject_draw(p_canvas->p_renderobject, p_program);
}

void canvas_destroy(t_canvas *p_canvas) {
    printf("canvas destroy\n");
    renderobject_destroy(p_canvas->p_renderobject);
    free(p_canvas);
}

