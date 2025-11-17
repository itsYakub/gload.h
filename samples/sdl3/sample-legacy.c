#define GLOAD_IMPLEMENTATION
#include "./../../gload.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>



int main(void) {
    SDL_Window      *window;
    SDL_GLContext   context;
    SDL_Event       event;

    if (!SDL_Init(SDL_INIT_VIDEO)) { return (1); }

    window = SDL_CreateWindow("gload.h - SDL3 sample", 800, 600, SDL_WINDOW_OPENGL);
    if (!window) { return (1); }

    context = SDL_GL_CreateContext(window);
    if (!context) { return (1); }

    if (!SDL_GL_MakeCurrent(window, context)) { return (1); }

    if (!gloadLoadGLLoader((t_gloadLoader) SDL_GL_GetProcAddress)) { return (1); }

    for (int exit = 0; !exit; ) {
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);


        glBegin(GL_QUADS);
            glVertex2f(-0.5,-0.5);
            glVertex2f(-0.5, 0.5);
            glVertex2f( 0.5, 0.5);
            glVertex2f( 0.5,-0.5);
        glEnd();


        SDL_GL_SwapWindow(window);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case (SDL_EVENT_QUIT): { exit = 1; } break;
            }
        }
    }


    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return (0);
}
