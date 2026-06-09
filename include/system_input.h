#pragma once
#include <stdbool.h>
#include <SDL2/SDL.h> // Fornisce la costante SDL_NUM_SCANCODES (circa 512 tasti)

typedef struct {
    // keyboard keys (for continuous behaviour)
    bool keys_down[SDL_NUM_SCANCODES];
    
    // instant keyboard keys (for toggle behaviour or a single click)
    bool keys_just_pressed[SDL_NUM_SCANCODES];

    // mouse state
    int mouse_x;               // x position
    int mouse_y;               // y position
    
    bool mouse_left_down;      // left button down (continuous)
    bool mouse_right_down;     // right button down (continuous)
    
    bool mouse_left_clicked;   // left click (toggle)
    bool mouse_right_clicked;  // right click (toggle)
    
    int click_x;               // x position when click is true
    int click_y;               // y position when click is true
    
    int mouse_wheel_scroll;    // > 0 if scroll up, < 0 if scroll down, 0 if stopped

    // system state (for example clicking the window's X)
    bool window_closed;        // quit input
} InputState;

// init the struct
void input_init(InputState *input);

// update the struct
void input_update(InputState *input);

// return true if the input is continuous
bool input_is_key_down(const InputState *input, SDL_Scancode scancode);

// return true if the input is toggle
bool input_is_key_just_pressed(const InputState *input, SDL_Scancode scancode);