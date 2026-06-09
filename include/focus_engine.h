#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "vector.h"
#include "system_input.h"

typedef struct
{
    int width, height; // screen width and height
    
    SDL_Renderer *renderer; 
    SDL_Window *window; 

    bool running; // runnning state of the engine

    float offsetx, offsety; // for pan 
    float scale;            // for zoom-in/out

    InputState input;

} FocusEngine;


typedef struct
{
    int r, g, b, a;
} Color;

// init the engine
void engine_init(FocusEngine *fe, float width, float height);

// destroy the engine
void engine_destroy(FocusEngine *fe);

// convert x coordinate to screen coordinate
float coordx_to_screenx(FocusEngine *fe, float x);

// convert y coordinate to screen coordinate
float coordy_to_screeny(FocusEngine *fe, float y);

// convert screen x coordinate back to world coordinate
float screenx_to_coordx(FocusEngine *fe, int x);

// convert screen y coordinate back to world coordinate
float screeny_to_coordy(FocusEngine *fe, int y);

// drawing system reference grid
void draw_grid(FocusEngine *fe);

// draw a circle
void draw_circle(FocusEngine *fe, float xc, float yc, float r, Color c);

// drawing a vector
void draw_vector(FocusEngine *fe, AppliedVector2D v, Color c);

// start the drawing frame
void start_frame(FocusEngine *fe);

// end the drawing frame
void end_frame(FocusEngine *fe);