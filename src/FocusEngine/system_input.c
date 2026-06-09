#include "FocusEngine/system_input.h"

// init the struct
void input_init(InputState *input) 
{
    // init to false all the keyboard keys
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) 
    {
        input->keys_down[i] = false;
        input->keys_just_pressed[i] = false;
    }

    // init the mouse state
    input->mouse_x = 0;
    input->mouse_y = 0;
    input->mouse_delta_x = 0;
    input->mouse_delta_y = 0;

    input->mouse_left_down = false;
    input->mouse_middle_down = false;
    input->mouse_right_down = false;
    input->mouse_left_clicked = false;
    input->mouse_middle_clicked = false;
    input->mouse_right_clicked = false;

    input->click_x = 0;
    input->click_y = 0;

    input->mouse_wheel_scroll = 0;

    
    input->window_closed = false;
}

// update the struct
void input_update(InputState *input) 
{
    SDL_Event event;

    // reset instantaneous events
    input->mouse_left_clicked = false;
    input->mouse_middle_clicked = false;
    input->mouse_right_clicked = false;
    input->mouse_wheel_scroll = 0;
    input->mouse_delta_x = 0;
    input->mouse_delta_y = 0;
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) 
    {
        input->keys_just_pressed[i] = false;
    }

    // update mouse state
    Uint32 mouse_buttons = SDL_GetMouseState(&input->mouse_x, &input->mouse_y);

    input->mouse_left_down = (mouse_buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
    input->mouse_middle_down = (mouse_buttons & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0;
    input->mouse_right_down = (mouse_buttons & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0;

    // poll events
    while (SDL_PollEvent(&event)) 
    {
        switch (event.type) 
        {
            case SDL_QUIT:
                input->window_closed = true;
                break;

            case SDL_KEYDOWN:
                if (event.key.repeat == 0) 
                {
                    SDL_Scancode scancode = event.key.keysym.scancode;
                    if (scancode < SDL_NUM_SCANCODES) 
                    {
                        input->keys_down[scancode] = true;
                        // this will be reset the next frame, so it's true only in this frame
                        input->keys_just_pressed[scancode] = true; 
                    }
                }
                break;

            case SDL_KEYUP:
                {
                    SDL_Scancode scancode = event.key.keysym.scancode;
                    if (scancode < SDL_NUM_SCANCODES) 
                    {
                        input->keys_down[scancode] = false;
                    }
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) 
                    input->mouse_left_clicked = true;
                else if (event.button.button == SDL_BUTTON_MIDDLE) 
                    input->mouse_middle_clicked = true;
                else if (event.button.button == SDL_BUTTON_RIGHT) 
                    input->mouse_right_clicked = true;
                    
                input->click_x = event.button.x;
                input->click_y = event.button.y;
                break;

            case SDL_MOUSEWHEEL:
                input->mouse_wheel_scroll = event.wheel.y; // 1 = ip, -1 = down
                break;

            case SDL_MOUSEMOTION:
                input->mouse_delta_x = event.motion.xrel;
                input->mouse_delta_y = event.motion.yrel;
                break;
        }
    }
}


// return true if the input is continuous
bool input_is_key_down(const InputState *input, SDL_Scancode scancode) 
{
    if (scancode >= SDL_NUM_SCANCODES) return false;
    return input->keys_down[scancode];
}


// return true if the input is toggle
bool input_is_key_just_pressed(const InputState *input, SDL_Scancode scancode) 
{
    if (scancode >= SDL_NUM_SCANCODES) return false;
    return input->keys_just_pressed[scancode];
}