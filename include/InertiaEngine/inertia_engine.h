#pragma once
#include <stdlib.h>
#include "InertiaEngine/body.h"

#define MAX_BODIES 1024
#define TIME_STEP 0.001 // simulation time step. Physics will run at 1KHz


typedef struct
{
    Body bodies[MAX_BODIES];
    int body_count; 

    // TODO: add springs and constraints


    double gravityx; 
    double gravityy; 

} InertiaEngine;


// init the physics engine
void inertia_init(InertiaEngine *ie, double gravityx, double gravityy);

// reset all the forces
void inertia_reset_forces(InertiaEngine *ie);

// create circle body 
Body* inertia_create_circle(InertiaEngine *ie, double px, double py, double vx, double vy, float radius, double mass);

// create box body 
Body* inertia_create_box(InertiaEngine *ie, double px, double py, double vx, double vy, float width, float height, double mass);

void inertia_update(InertiaEngine *ie);