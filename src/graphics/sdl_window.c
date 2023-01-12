#include "sdl_window.h"
#include <SDL2/SDL_video.h>


t_sdl_window *sdl_window_new(int width, int height) {
    t_sdl_window *p_sdl_window = calloc(1, sizeof(t_sdl_window));
    sdl_window_init(p_sdl_window, width, height);
    return p_sdl_window;
}

void sdl_window_init(t_sdl_window *p_sdl_window, int width, int height) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf( "opengl could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    SDL_GL_LoadLibrary(NULL);
    
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    p_sdl_window->p_window = SDL_CreateWindow(
        "widgets",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_OPENGL
    );
    
    if (p_sdl_window->p_window == NULL) {
        printf( "window could not be created! SDL_Error: %s\n", SDL_GetError());
    }
    
    // context
    p_sdl_window->context = SDL_GL_CreateContext(p_sdl_window->p_window);
    if (p_sdl_window->context == NULL) {
        printf("context could not be created! SDL_Error: %s\n", SDL_GetError());
    }
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        printf("failed to initialize opengl context");
    }
    printf("%s, glsl: %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

    p_sdl_window->running = 1;
}

void sdl_window_event(t_sdl_window *p_sdl_window) {
    while (SDL_PollEvent(&p_sdl_window->event)) {
        if (p_sdl_window->event.type == SDL_QUIT) {
            p_sdl_window->running = 0;
            break;
        }
        if (p_sdl_window->event.type == SDL_KEYDOWN) {
            switch (p_sdl_window->event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    p_sdl_window->running = 0;
                    break;
                case SDLK_a:
                    printf("hello\n");
                    p_sdl_window->running = 1;
                    break;
                default:
                    p_sdl_window->running = 1;
                    break;
            }
        }
    }
}

void sdl_window_update(t_sdl_window *p_sdl_window) {
    SDL_GL_SwapWindow(p_sdl_window->p_window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void sdl_window_destroy(t_sdl_window *p_sdl_window) {
    SDL_GL_DeleteContext(p_sdl_window->context);
    SDL_DestroyWindow(p_sdl_window->p_window);
    SDL_Quit();
    free(p_sdl_window);
}

