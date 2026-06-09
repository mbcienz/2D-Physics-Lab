#include "focus_engine.h"

int main(int argc, char *argv[])
{
    FocusEngine fe;
    engine_init(&fe, 900, 600);

    Vector2D origin = {0.0, 0.0};
    Vector2D end = {1.0, 1.0};

    Vector2D circle = {10.0, 10.0};
    float r = 4.0;

    AppliedVector2D vect = {origin, end};
    
    Color c = {255, 0, 0, 255};
    
    // main loop
    while( fe.running )
    {
        input_update(&fe.input);

        if (fe.input.window_closed)
            fe.running = false;

        if (fe.input.mouse_left_down)
            camera_pan(&fe.camera, fe.input.mouse_delta_x, fe.input.mouse_delta_y);
        
        if (fe.input.mouse_wheel_scroll > 0.0)
            camera_zoom(&fe.camera, 1.1);
        else if (fe.input.mouse_wheel_scroll < 0.0)
            camera_zoom(&fe.camera, 0.9);

        // draw
        start_frame(&fe);
        draw_grid(&fe);
        draw_vector(&fe, vect, c);
        draw_circle(&fe, circle, r, c);
        end_frame(&fe);

    }

    engine_destroy(&fe);

    return 0;
}