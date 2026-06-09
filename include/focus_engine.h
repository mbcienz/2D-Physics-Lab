#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "vector.h"
#include "system_input.h"
#include "camera.h"

typedef struct
{
    int width, height; // screen width and height
    
    // sdl references
    SDL_Renderer *renderer; 
    SDL_Window *window; 

    // engine state
    bool running; // runnning state of the engine
    bool show_fps;

    // engine components
    TTF_Font *font;
    InputState input;
    Camera2D camera;

} FocusEngine;


typedef struct
{
    int r, g, b, a;
} Color;

// init the engine
void engine_init(FocusEngine *fe, float width, float height);

// destroy the engine
void engine_destroy(FocusEngine *fe);

// toggle running state
void toggle_running(FocusEngine *fe);

// toggle fps state
void toggle_show_fpw(FocusEngine *fe);

// convert x coordinate to screen coordinate
float coordx_to_screenx(FocusEngine *fe, float x);

// convert y coordinate to screen coordinate
float coordy_to_screeny(FocusEngine *fe, float y);

// convert screen x coordinate back to world coordinate
float screenx_to_coordx(FocusEngine *fe, int x);

// convert screen y coordinate back to world coordinate
float screeny_to_coordy(FocusEngine *fe, int y);

// drawing system reference grid. This is used for real object which scales with the camera zoom
void draw_grid(FocusEngine *fe);

// draw a circle in world coordinate. This i used for fixed object which doesn't scale with the camera zoom
void draw_circle(FocusEngine *fe, Vector2D center, float r, Color c);

// draw a circle in screen coordinate
void draw_circle_screen(FocusEngine *fe, Vector2D center, int pixel_r, Color c);

// drawing a vector
void draw_vector(FocusEngine *fe, AppliedVector2D v, Color c);

// show FPS
void render_fps(FocusEngine *fe);

// start the drawing frame
void start_frame(FocusEngine *fe);

// end the drawing frame
void end_frame(FocusEngine *fe);