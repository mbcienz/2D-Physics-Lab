#include "FocusEngine/focus_engine.h"

// init the engine
void engine_init(FocusEngine *fe, float width, float height)
{
	fe->width = width;
	fe->height = height; 
    
	fe->window = NULL;
	fe->renderer = NULL; 
	
    // time control
    fe->last_frame_ticks = SDL_GetTicks();
    fe->delta_time = 0.0;
	// state
	fe->running = false;
	fe->show_fps = true;

	// SDL init
	if( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		printf("SDL Init error!\n");
		return;
	}

	// Window and renderer creation
	if( SDL_CreateWindowAndRenderer(fe->width, fe->height, SDL_WINDOW_RESIZABLE, &fe->window, &fe->renderer) )
	{
		printf("SDL Window and renderer creation error\n");
		return;
	}
	
	// Init the ttf font
	if ( TTF_Init() == -1 )
		printf("Error in TTF_Init()! You will not be able to see texts: %s", TTF_GetError());

	// load the font
    fe->font = TTF_OpenFont("assets/fonts/tecnico/TecnicoFino-xX70.ttf", 18);
    if (!fe->font) {
        printf("Errore caricamento font: %s\n", TTF_GetError());
    }


	camera_init(&fe->camera);
	input_init(&fe->input);

	fe->running = true;
}

// destroy the engine
void engine_destroy(FocusEngine *fe)
{
	// Close the font
	if (fe->font) {
        TTF_CloseFont(fe->font);
    }
	TTF_Quit();

	fe->running = false; 
	fe->show_fps = false; 

	SDL_DestroyRenderer(fe->renderer); 
	SDL_DestroyWindow(fe->window);
	SDL_Quit();
}


// toggle running state
void toggle_running(FocusEngine *fe)
{
	fe->running = !fe->running;
}

// toggle fps state
void toggle_show_fpw(FocusEngine *fe)
{
	fe->show_fps = !fe->show_fps;
}


// convert x coordinate to screen coordinate
float coordx_to_screenx(FocusEngine *fe, float x)
{
	return fe->width/2 + fe->camera.offsetx + (x * fe->camera.scale);
}


// convert y coordinate to screen coordinate
float coordy_to_screeny(FocusEngine *fe, float y)
{
	return fe->height/2 + fe->camera.offsety - (y * fe->camera.scale);
}

// convert screen x coordinate back to world coordinate
float screenx_to_coordx(FocusEngine *fe, int x)
{
    return (x - (fe->width / 2.0f) - fe->camera.offsetx) / fe->camera.scale;
}

// convert screen y coordinate back to world coordinate
float screeny_to_coordy(FocusEngine *fe, int y)
{
    return ((fe->height / 2.0f) + fe->camera.offsety - y) / fe->camera.scale;
}


// drawing system reference grid
void draw_grid(FocusEngine *fe)
{
	int i; 

	float min_x = screenx_to_coordx(fe, 0);
    float max_x = screenx_to_coordx(fe, fe->width);
    float min_y = screeny_to_coordy(fe, fe->height); 
    float max_y = screeny_to_coordy(fe, 0);
	
	// vertical lines
	SDL_SetRenderDrawColor(fe->renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
	for( i = min_x; i <= max_x; i++ )
	{
		SDL_RenderDrawLine(fe->renderer, coordx_to_screenx(fe, i), 0, coordx_to_screenx(fe, i), fe->height);
	}	

	// horizontal lines
	for (i = min_y; i <= max_y; i++ )
	{
		SDL_RenderDrawLine(fe->renderer, 0, coordy_to_screeny(fe, i), fe->width, coordy_to_screeny(fe, i));
	}


	// draw axes 
	// vertical axes : green
	SDL_SetRenderDrawColor(fe->renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(fe->renderer, coordx_to_screenx(fe, 0.0), 0, coordx_to_screenx(fe, 0.0), fe->height);
	// horizontal axes : red
	SDL_SetRenderDrawColor(fe->renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(fe->renderer, 0, coordy_to_screeny(fe, 0.0), fe->width, coordy_to_screeny(fe, 0.0));

	// origin : yellow.
	// The origin is a circle in (0, 0)
	int r = 5.0; // 5px radius
    Color c = {255, 255, 0, 255};
	Vector2D circle = {0.0 , 0.0};
	draw_circle_screen(fe, circle, r, c);	

	// set the color back to black
	SDL_SetRenderDrawColor(fe->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}


// draw a circle ( IN WORLD COORDINATE ). The function uses the Scanline Circle Algorithm
void draw_circle(FocusEngine *fe, Vector2D center, float r, Color c) 
{
    SDL_SetRenderDrawColor(fe->renderer, c.r, c.g, c.b, c.a);

    int cx = coordx_to_screenx(fe, center.x);
    int cy = coordy_to_screeny(fe, center.y); 
    int radius = (int)(r * fe->camera.scale);

    if (radius <= 0) return;

    // clip if is out of the screen
    if (cx + radius < 0 || cx - radius >= fe->width || cy + radius < 0 || cy - radius >= fe->height) 
		return;

    int x = radius;
    int y = 0;
    int x_change = 1 - 2 * radius;
    int y_change = 1;
    int radius_error = 0;

    while (x >= y) {
        // draw bottom half, mirrored on x axis.
        int y1 = cy + y;
        int y2 = cy - y;
        if (y1 >= 0 && y1 < fe->height) {
            int left = (cx - x) < 0 ? 0 : (cx - x);
            int right = (cx + x) >= fe->width ? fe->width - 1 : (cx + x);
            if (left <= right) SDL_RenderDrawLine(fe->renderer, left, y1, right, y1);
        }
        if (y2 >= 0 && y2 < fe->height && y != 0) { 
            int left = (cx - x) < 0 ? 0 : (cx - x);
            int right = (cx + x) >= fe->width ? fe->width - 1 : (cx + x);
            if (left <= right) SDL_RenderDrawLine(fe->renderer, left, y2, right, y2);
        }

        // draw upper half, mirrored on x axis
        int y3 = cy + x;
        int y4 = cy - x;
        if (y3 >= 0 && y3 < fe->height && x != y) {
            int left = (cx - y) < 0 ? 0 : (cx - y);
            int right = (cx + y) >= fe->width ? fe->width - 1 : (cx + y);
            if (left <= right) SDL_RenderDrawLine(fe->renderer, left, y3, right, y3);
        }
        if (y4 >= 0 && y4 < fe->height && x != y) {
            int left = (cx - y) < 0 ? 0 : (cx - y);
            int right = (cx + y) >= fe->width ? fe->width - 1 : (cx + y);
            if (left <= right) SDL_RenderDrawLine(fe->renderer, left, y4, right, y4);
        }

		// update the perimeter
        y++;
        radius_error += y_change;
        y_change += 2;
        if (2 * radius_error + x_change > 0) {
            x--;
            radius_error += x_change;
            x_change += 2;
        }
    }
}

// draw a circle with a fixed radius in screen pixels ( NOT WORLD COORDINATE). 
// The function uses the Scanline Circle Algorithm
void draw_circle_screen(FocusEngine *fe, Vector2D center, int pixel_r, Color c)
{
    SDL_SetRenderDrawColor(fe->renderer, c.r, c.g, c.b, c.a);

    int cx = coordx_to_screenx(fe, center.x);
    int cy = coordy_to_screeny(fe, center.y);

    if (pixel_r <= 0) return;

    // clip if is out of the screen
    if (cx + pixel_r < 0 || cx - pixel_r >= fe->width || cy + pixel_r < 0 || cy - pixel_r >= fe->height) 
		return;

    int x = pixel_r;
    int y = 0;
    int x_change = 1 - 2 * pixel_r;
    int y_change = 1;
    int radius_error = 0;

    while (x >= y) {
        // draw bottom half, mirrored on x axis.
        int y1 = cy + y;
        int y2 = cy - y;
        if (y1 >= 0 && y1 < fe->height) {
            int left = (cx - x) < 0 ? 0 : (cx - x);
            int right = (cx + x) >= fe->width ? fe->width - 1 : (cx + x);
            if (left <= right) SDL_RenderDrawLine(fe->renderer, left, y1, right, y1);
        }
        if (y2 >= 0 && y2 < fe->height && y != 0) {
            int left = (cx - x) < 0 ? 0 : (cx - x);
            int right = (cx + x) >= fe->width ? fe->width - 1 : (cx + x);
            if (left <= right) SDL_RenderDrawLine(fe->renderer, left, y2, right, y2);
        }

        // draw upper half, mirrored on x axis
        int y3 = cy + x;
        int y4 = cy - x;
        if (y3 >= 0 && y3 < fe->height && x != y) {
            int left = (cx - y) < 0 ? 0 : (cx - y);
            int right = (cx + y) >= fe->width ? fe->width - 1 : (cx + y);
            if (left <= right) SDL_RenderDrawLine(fe->renderer, left, y3, right, y3);
        }
        if (y4 >= 0 && y4 < fe->height && x != y) {
            int left = (cx - y) < 0 ? 0 : (cx - y);
            int right = (cx + y) >= fe->width ? fe->width - 1 : (cx + y);
            if (left <= right) SDL_RenderDrawLine(fe->renderer, left, y4, right, y4);
        }

		// update the perimeter
        y++;
        radius_error += y_change;
        y_change += 2;
        if (2 * radius_error + x_change > 0) {
            x--;
            radius_error += x_change;
            x_change += 2;
        }
    }
}



// drawing a vector
void draw_vector(FocusEngine *fe, AppliedVector2D v, Color c)
{
	SDL_SetRenderDrawColor(fe->renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawLine(fe->renderer, coordx_to_screenx(fe, v.origin.x), coordy_to_screeny(fe, v.origin.y), 
                                    coordx_to_screenx(fe, v.end.x), coordy_to_screeny(fe, v.end.y));
	draw_circle_screen(fe, v.end, 5.0, c);
}


// show FPS
void render_fps(FocusEngine *fe)
{
	// if font doesn't load properly don't render
	if (!fe->show_fps || !fe->font) return;

    static uint32_t last_time = 0;
    static int fps = 0;				// fps count
    static int frame_count = 0;		// frame count

    uint32_t current_time = SDL_GetTicks();
    frame_count++;

    if (current_time - last_time >= 1000) {
        fps = frame_count;
        frame_count = 0;
        last_time = current_time;
    }

    // prepare the text, for example "FPS : 144"
    char fps_text[20];
    sprintf(fps_text, "FPS: %d", fps);

    // prepare a surface and generate the white text
    SDL_Color text_color = { 255, 255, 255, 255 };
    SDL_Surface *text_surface = TTF_RenderText_Blended(fe->font, fps_text, text_color);
    if (!text_surface) return;

    // load the text to gpu as texture
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(fe->renderer, text_surface);
    
    if (text_texture) {
        // place  the text in the top right of the screen
        SDL_Rect dest_rect = { 
            fe->width - text_surface->w - 15, 	// left margin
            15,               					// top margin
            text_surface->w,   					// surface width 
            text_surface->h 					// surface height
        };

        SDL_RenderCopy(fe->renderer, text_texture, NULL, &dest_rect);

        // delete the resources
        SDL_DestroyTexture(text_texture);
    }

    SDL_FreeSurface(text_surface);
}


// start the drawing frame
void start_frame(FocusEngine *fe)
{
    uint32_t current_tick = SDL_GetTicks();
    uint32_t delta_time = current_tick - fe->last_frame_ticks;

    // convert ms in seconds
    fe->delta_time = delta_time / 1000.0; 

    fe->last_frame_ticks = current_tick;

    SDL_SetRenderDrawColor(fe->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(fe->renderer);
}


// end the drawing frame
void end_frame(FocusEngine *fe)
{
	if ( fe->show_fps )
		render_fps(fe);
    SDL_RenderPresent(fe->renderer);
}