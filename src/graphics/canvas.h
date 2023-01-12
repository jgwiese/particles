#ifndef CANVAS_H
#define CANVAS_H

#include "renderobject.h"
#include "mesh.h"
#include "program.h"


typedef struct {
    t_mesh *p_mesh;
    t_renderobject *p_renderobject;
} t_canvas;

t_canvas *canvas_new();
void canvas_init(t_canvas *p_canvas);
void canvas_draw(t_canvas *p_canvas, t_program *p_program);
void canvas_destroy(t_canvas *p_canvas);

#endif // CANVAS_H

