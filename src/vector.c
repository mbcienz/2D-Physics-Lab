#include "vector.h"

// scalar mutiplication
Vector2D scalar_mult(type_t k, Vector2D v)
{
    Vector2D r; 
    r.x = v.x * k;
    r.y = v.y * k;

    return r;
}


// sum two vectors
Vector2D vector_sum(Vector2D v1, Vector2D v2)
{
    Vector2D r; 
    r.x = v1.x + v2.x; 
    r.y = v1.y + v2.y; 

    return r; 
}


// subtract two vectors
Vector2D vector_sub(Vector2D v1, Vector2D v2)
{
    Vector2D r; 
    r.x = v1.x - v2.x; 
    r.y = v1.y - v2.y; 

    return r;
}


// division
Vector2D vector_div(Vector2D v1, type_t k)
{
    Vector2D r = {0.0 , 0.0};
    if ( k == 0.0 )
    {
        printf("Division by 0 not allowed!\n");
        return r;
    }
    r.x = v1.x / k; 
    r.y = v1.y / k; 
    return r;
}


// vector magnitude
type_t vector_mag(Vector2D v1)
{
    return (type_t) sqrt(v1.x * v1.x + v1.y * v1.y);
}


// vector normalization
Vector2D vector_normalize(Vector2D v1)
{
    type_t mag = vector_mag(v1);
    Vector2D norm = {0.0, 0.0}; 
    if (mag == 0.0)
    {
        printf("Can not normalize this vector!\n");
        return norm;
    }
    norm.x = v1.x / mag; 
    norm.y = v1.y / mag; 
    return norm;
}


//dot product
type_t dot_product(Vector2D v1, Vector2D v2)
{
    return v1.x * v2.x  +  v1.y * v2.y;
}


//cross product
type_t cross_product(Vector2D v1, Vector2D v2)
{
    return v1.x * v2.y - v1.y * v2.x;
}


// angle between two vectors
type_t angle_between(Vector2D v1, Vector2D v2)
{
    type_t dot_prod = dot_product(v1, v2);
    type_t mag_prod = vector_mag(v1) * vector_mag(v2);

    if( mag_prod != 0.0)
    {
        type_t cos_theta = dot_prod / mag_prod;
        if (cos_theta > 1.0) cos_theta = 1.0;
        if (cos_theta < -1.0) cos_theta = -1.0;

        return rad2deg(acos(cos_theta));

    }

    return 0.0;
}

