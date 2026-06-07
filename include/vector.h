#pragma once
#include "const.h"

typedef struct
{
    type_t x; 
    type_t y; 
}  Vector2D;

typedef struct
{
    Vector2D origin;
    Vector2D end;
} AppliedVector2D;

// scalar mutiplication
void scalar_mult(type_t k, Vector2D *v, Vector2D *result);

// sum two vectors
void vector_sum(Vector2D *v1, Vector2D *v2, Vector2D *result);

// subtract two vectors
void vector_sub(Vector2D *v1, Vector2D *v2, Vector2D *result);
