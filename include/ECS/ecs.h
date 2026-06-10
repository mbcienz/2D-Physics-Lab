#pragma once
#include <stdbool.h>
#include "InertiaEngine/inertia_engine.h"
#include "FocusEngine/focus_engine.h"

typedef struct
{
    Body *b;
    Color c; 
    
} Entity;

typedef struct
{
    FocusEngine *fe; 
    InertiaEngine *ie;

    //entity
    Entity entity[MAX_BODIES];
    int count;

    // components
    bool show_forces_vector;
    
} ECS;

// init the engine
void ecs_scene_init(ECS *ecs, FocusEngine *fe, InertiaEngine *ie);

// create an entity
void ecs_create_entity(ECS *ecs, Body *b, Color c);

// draw scene
void ecs_draw_scene(ECS *ecs);

// toggle the vector forces view
void ecs_toggle_forces_draw(ECS *ecs);