#include "InertiaEngine/body.h"


// init the circle body
void body_init_circle(Body *b, double px, double py,  double vx, double vy, float radius, double mass)
{
    // body general information
    b->px = px; 
    b->py = py; 
    b->vx = vx;
    b->vy = vy;
    b->fx = 0.0;
    b->fy = 0.0;

    if (mass > 0.0) {
        b->mass = mass;
        b->inv_mass = 1.0 / mass;
    } else {
        b->mass = 0.0;     // used for static or very large (infinity) bodies
        b->inv_mass = 0.0;
    }

    // shape information
    b->shape.type = SHAPE_CIRCLE;
    b->shape.data.circle.radius = radius;
}

// init the box body
void body_init_box(Body *b, double px, double py,  double vx, double vy, float width, float height, double mass)
{
    // body general information
    b->px = px; 
    b->py = py; 
    b->vx = vx;
    b->vy = vy;
    b->fx = 0.0;
    b->fy = 0.0;
    if (mass > 0.0) {
        b->mass = mass;
        b->inv_mass = 1.0 / mass;
    } else {
        b->mass = 0.0;     // used for static or very large (infinity) bodies
        b->inv_mass = 0.0;
    }

    // shape information
    b->shape.type = SHAPE_BOX;
    b->shape.data.box.width = width; 
    b->shape.data.box.height = height; 
}

// apply force to a body
void body_apply_force(Body *b, double fx, double fy)
{
    b->fx += fx;
    b->fy += fy;
}


// get circle structure properties
CircleShape get_circle_properties(Body *b)
{
    assert(b->shape.type == SHAPE_CIRCLE);
    return b->shape.data.circle;
}

// get box structure properties
BoxShape get_box_properties(Body *b)
{
    assert(b->shape.type == SHAPE_BOX);
    return b->shape.data.box;
}