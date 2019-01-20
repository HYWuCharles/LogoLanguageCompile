#include "SDLutil.h"

#define PI 3.1415926535

void updateScreen(Window *w);

void init(Window *w){
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Unable to initialize SDL\n");
        SDL_Quit();
        exit(3);
    }

    w->finished = 0;
    w->current_x = WINDOW_W/2;
    w->current_y = WINDOW_H/2;
    w->angle = 0;

    w->win = SDL_CreateWindow("SDL Window",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            WINDOW_H,
                            WINDOW_W,
                            SDL_WINDOW_SHOWN);

    if (w->win == NULL){
        printf("Unable to initialize SDL\n");
        SDL_Quit();
        exit(3);
    }
    w->renderer = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (w->win == NULL){
        printf("Unable to initialize SDL\n");
        SDL_Quit();
        exit(3);
    }
    SDL_SetRenderDrawBlendMode(w->renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(w->renderer, 0, 0, 0, 255);
    SDL_RenderClear(w->renderer);
}

void drawLine(Window* w, int distance){
    int cur_x, cur_y, tar_x, tar_y, angle;
    float rad;
    cur_x = w->current_x;
    cur_y = w->current_y;
    angle = w->angle;
    /* Calculate rad */
    rad = angle*PI/180;
    tar_x = cur_x+distance*sin(rad);
    tar_y = cur_y+distance*cos(rad);
    SDL_SetRenderDrawColor(w->renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(w->renderer, cur_x, cur_y, tar_x, tar_y);
    w->current_x = tar_x;
    w->current_y = tar_y;
    updateScreen(w);
}

void drawCircleWithoutFilling(Window* w, int cx, int cy, int r){
    double dx, dy;
    SDL_SetRenderDrawColor(w->renderer, 255, 255, 255, 255);
    dx = floor(sqrt((2.0 * r ) ));
    SDL_RenderDrawLine(w->renderer, cx-dx, cy+r, cx+dx, cy+r);
    SDL_RenderDrawLine(w->renderer, cx-dx, cy-r, cx+dx, cy-r);
    for (dy = 1; dy <= r; dy += 1.0) {
        dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
        SDL_RenderDrawPoint(w->renderer, cx+dx, cy+r-dy);
        SDL_RenderDrawPoint(w->renderer, cx+dx, cy-r+dy);
        SDL_RenderDrawPoint(w->renderer, cx-dx, cy+r-dy);
        SDL_RenderDrawPoint(w->renderer, cx-dx, cy-r+dy);
   }
}

void updateScreen(Window *w){
    SDL_SetRenderTarget(w->renderer, NULL);
    SDL_RenderPresent(w->renderer);
}

void exitEvent(Window* w){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_KEYDOWN:
                w->finished = 1;
        }
    }
}
