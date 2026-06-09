#include "focus_engine.h"
#include "system_input.h"
#include "vector.h"

int main(int argc, char *argv[])
{
    FocusEngine fe;
    engine_init(&fe, 900, 600);


    Vector2D origin = {0.0, 0.0};
    Vector2D end = {1.0, 1.0};

    AppliedVector2D vect = {origin, end};
    
    Color c = {255, 0, 0, 255};
    
    // main loop
    while( fe.running )
    {
        input_update(&fe.input);

        if (fe.input.window_closed)
            fe.running = false;

        // update end vector
        vect.end.x = screenx_to_coordx(&fe, fe.input.mouse_x);
        vect.end.y = screeny_to_coordy(&fe, fe.input.mouse_y);

        
        // draw
        start_frame(&fe);
        draw_grid(&fe);
        draw_vector(&fe, vect, c);
        end_frame(&fe);

    }

    engine_destroy(&fe);

    return 0;
}