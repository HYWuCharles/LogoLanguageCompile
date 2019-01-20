#ifndef SDLUTIL_H
#define SDLUTIL_H

#include <SDL.h>
#include <math.h>


#define WINDOW_H 800
#define WINDOW_W 800

typedef struct SDL_WINDOW {
    SDL_bool finished;
    SDL_Window *win;
    SDL_Renderer *renderer;
    int current_x; /* now where x */
    int current_y; /* now where y*/
    int angle; /* now angle relative to verticle */
}Window;

void init(Window *w);
void drawLine(Window *w, int distance);
void drawCircleWithoutFilling(Window* w, int cx, int cy, int r);
void exitEvent(Window* w);

#endif 
