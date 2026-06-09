#include "InertiaEngine/inertia_engine.h"

// init the physics engine
void inertia_init(InertiaEngine *ie, double gravityx, double gravityy)
{
    ie->body_count = 0;
    ie->gravityx = gravityx;
    ie->gravityy = gravityy;
}


// create circle body 
Body* inertia_create_circle(InertiaEngine *ie, double px, double py, double vx, double vy, float radius, double mass)
{
    // if there is alread the max number of bodies, don't create a new body
    if ( ie->body_count >= MAX_BODIES ) 
        return NULL;

    // create a new body
    Body *b = &ie->bodies[ie->body_count]; 
    body_init_circle(b, px, py, vx, vy, radius, mass);
    ie->body_count++;

    return b;
}


// create box body 
Body* inertia_create_box(InertiaEngine *ie, double px, double py, double vx, double vy, float width, float height, double mass)
{
    // if there is alread the max number of bodies, don't create a new body
    if ( ie->body_count >= MAX_BODIES ) 
        return NULL;

    // create a new body
    Body *b = &ie->bodies[ie->body_count]; 
    body_init_box(b, px, py, vx, vy, width, height, mass);
    ie->body_count++;

    return b;
}


void inertia_update(InertiaEngine *ie)
{
    int i; 
    // apply forces to every body
    for ( i = 0; i < ie->body_count; i++ )
    {   
        Body *b = &ie->bodies[i];
        // apply the gravity force: F = m * g
        body_apply_force(b, b->mass * ie->gravityx, b->mass * ie->gravityy);

        // TODO: future forces implementation
    }

    // update velocity and position given the forces on every body
    for ( i = 0; i < ie->body_count; i++ )
    {
        Body *b = &ie->bodies[i];
        // if it's an fixed body, continue
        if (b->inv_mass == 0.0) continue;
        // update the velocity : v = v0 +  F / m * time_step
        b->vx += ( b->fx * b->inv_mass ) * TIME_STEP;
        b->vy += ( b->fy * b->inv_mass ) * TIME_STEP;
        // update the position : p = p0 + v * time_step
        b->px += b->vx * TIME_STEP;
        b->py += b->vy * TIME_STEP;

        // reset the forces for the next simulation step
        b->fx = 0.0;
        b->fy = 0.0;
    }


}