#pragma once
#include <stdio.h>
#include "const.h"
#include <math.h>
#include <stdlib.h>
#include "math_utility.h"

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
Vector2D scalar_mult(type_t k, Vector2D v);

// sum two vectors
Vector2D vector_sum(Vector2D v1, Vector2D v2);

// subtract two vectors
Vector2D vector_sub(Vector2D v1, Vector2D v2);

// division
Vector2D vector_div(Vector2D v1, type_t v2);

// vector magnitude
type_t vector_mag(Vector2D v1);

// vector normalization
Vector2D vector_normalize(Vector2D v1);

//dot product
type_t dot_product(Vector2D v1, Vector2D v2);

//cross product
type_t cross_product(Vector2D v1, Vector2D v2);

// angle between two vectors
type_t angle_between(Vector2D v1, Vector2D v2);