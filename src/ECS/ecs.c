#include "ECS/ecs.h"

// init the engine
void ecs_scene_init(ECS *ecs, FocusEngine *fe, InertiaEngine *ie)
{
    ecs->fe = fe;
    ecs->ie = ie;
    ecs->count = 0;
}


// create an entity
void ecs_create_entity(ECS *ecs, Body *b, Color c)
{
    Entity e = {b, c};
    ecs->entity[ecs->count] = e;
    ecs->count++;
    ecs->show_forces_vector = true;
}

// draw scene
void ecs_draw_scene(ECS *ecs)
{
    int i; 
    for ( i = 0; i < ecs->count; i++ )
    {
        Entity e = ecs->entity[i];
        Vector2D center = {e.b->px, e.b->py};
        if ( e.b->shape.type == SHAPE_CIRCLE){
            CircleShape prop = get_circle_properties(e.b);
            draw_circle(ecs->fe, center, prop.radius, e.c);
        }

        // TODO: BOXES
        /*
        if ( e.b->shape.type == SHAPE_BOX){
            BoxShape prop = get_box_properties(e.b);
            draw_box(ecs->fe, center, prop.width, prop.height, e.c);
        }
        */
        if (ecs->show_forces_vector)
        {
            double fx = e.b->fx;
            double fy = e.b->fy;

            if (fx != 0.0 || fy != 0.0)
            {
                // 1. Calcolo della magnitudo (Teorema di Pitagora)
                double magnitude = sqrt(fx * fx + fy * fy);

                // 2. Normalizzazione per ottenere il versore (nx, ny)
                double nx = fx / magnitude;
                double ny = fy / magnitude;

                // 3. Lunghezza fissa arbitraria espressa in coordinate mondo
                float fixed_world_length = 2.0f; 

                AppliedVector2D ap;
                ap.origin = center;
                ap.end.x = center.x + (nx * fixed_world_length);
                ap.end.y = center.y + (ny * fixed_world_length);

                draw_vector(ecs->fe, ap, (Color) {255, 255, 255, 255});
            }
        }
    }
}


// toggle the vector forces view
void ecs_toggle_forces_draw(ECS *ecs)
{
    ecs->show_forces_vector = !ecs->show_forces_vector;
}