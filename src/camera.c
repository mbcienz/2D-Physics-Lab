 #include "camera.h"

// init the camera
void camera_init(Camera2D *camera)
{
    camera->offsetx = 0.0;
    camera->offsety = 0.0;
    camera->scale = 40.0;

}

// zoom in or out
void camera_zoom(Camera2D *camera, float scale, float offsetx, float offsety)
{
    float old_scale = camera->scale;
    camera->scale *= scale;
    
    // clamp scale to prevent inversion or extreme values
    if (camera->scale < 0.1f)   camera->scale = 0.1f;
    if (camera->scale > 1000.0f) camera->scale = 1000.0f;
    
    float delta_scale = camera->scale - old_scale;

    // update the offset to zoom-in/out from the mouse position
    camera->offsetx -= offsetx * delta_scale;
    camera->offsety += offsety * delta_scale;
    
}

// traslate in the 2D plane
void camera_pan(Camera2D *camera, float offsetx, float offsety)
{
    camera->offsetx += offsetx;
    camera->offsety += offsety;
}