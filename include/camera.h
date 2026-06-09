#pragma once

typedef struct
{
    float offsetx, offsety; // for pan 
    float scale;            // for zoom-in/out
} Camera2D;

// init the camera
void camera_init(Camera2D *camera);

// zoom in or out
void camera_zoom(Camera2D *camera, float delta_scale);

// traslate in the 2D plane
void camera_pan(Camera2D *camera, float offsetx, float offsety);