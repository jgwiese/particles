#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include <glad/glad.h>
#include <SDL2/SDL.h>


typedef struct {
    SDL_Window *p_window;
    SDL_GLContext context;
    SDL_Event event;
    int running;
} t_sdl_window;

t_sdl_window *sdl_window_new(int width, int height);
void sdl_window_init(t_sdl_window *p_sdl_window, int width, int height);
void sdl_window_event(t_sdl_window *p_sdl_window);
void sdl_window_update(t_sdl_window *p_sdl_window);
void sdl_window_destroy(t_sdl_window *p_sdl_window);

#endif // SDL_WINDOW_H

