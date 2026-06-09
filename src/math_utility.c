#include "math_utility.h"


type_t deg2rad(type_t deg)
{
    return (deg * PI) / (type_t) 180;
}

type_t rad2deg(type_t rad)
{
    return (rad * (type_t) 180) / PI;
}