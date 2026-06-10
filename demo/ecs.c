#include "FocusEngine/focus_engine.h"
#include "InertiaEngine/inertia_engine.h"
#include "ECS/ecs.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FocusEngine fe;
    engine_init(&fe, 900, 600);

    InertiaEngine ie; 
    inertia_init(&ie, 3.0, -9.81);

    ECS ecs; 
    ecs_scene_init(&ecs, &fe, &ie);
    //ecs_toggle_forces_draw(&ecs);

    srand(0); 

    // accumulator for the phyysics engine
    double accumulator = 0.0;
    // main loop
    while( fe.running )
    {
        // manage the time 
        start_frame(&fe);
        accumulator += fe.delta_time;

        input_update(&fe.input);

        if (fe.input.window_closed)
            fe.running = false;

        if (fe.input.mouse_middle_down)
            camera_pan(&fe.camera, fe.input.mouse_delta_x, fe.input.mouse_delta_y);
        
        if (fe.input.mouse_wheel_scroll > 0.0)
            camera_zoom(&fe.camera, 1.1, screenx_to_coordx(&fe, fe.input.mouse_x), screeny_to_coordy(&fe, fe.input.mouse_y));
        else if (fe.input.mouse_wheel_scroll < 0.0)
            camera_zoom(&fe.camera, 0.9, screenx_to_coordx(&fe, fe.input.mouse_x), screeny_to_coordy(&fe, fe.input.mouse_y));


        // spawn a new body
        if ( fe.input.mouse_left_clicked )
        {            
            Body *b = inertia_create_circle(&ie, screenx_to_coordx(&fe, fe.input.click_x), screeny_to_coordy(&fe, fe.input.click_y),
                                                0.0, 0.0, (rand() % 5) + 1.0, (rand() % 100) + 1.0);
            
            Color c = {
                rand() % 256, // red
                rand() % 256, // green
                rand() % 256, // blue
                255, // alpha
            };           
            ecs_create_entity(&ecs, b, c); 
        }

        while ( accumulator >= TIME_STEP)
        {
            inertia_reset_forces(&ie);
            inertia_update(&ie);
            accumulator -= TIME_STEP;
        }

        // draw
        draw_grid(&fe);
        
        ecs_draw_scene(&ecs);

        end_frame(&fe);

    }

    engine_destroy(&fe);
    

    return 0;
}