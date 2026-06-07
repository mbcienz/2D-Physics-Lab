#include "../include/vector.h"

// scalar mutiplication
void scalar_mult(type_t k, Vector2D *v, Vector2D *result)
{
    result->x = v->x * k;
    result->y = v->y * k;
}

// sum two vectors
void vector_sum(Vector2D *v1, Vector2D *v2, Vector2D *result)
{
    result->x = v1->x + v2->x; 
    result->y = v1->y + v2->y; 
}

// subtract two vectors
void vector_sub(Vector2D *v1, Vector2D *v2, Vector2D *result)
{
    result->x = v1->x - v2->x; 
    result->y = v1->y - v2->y; 
}