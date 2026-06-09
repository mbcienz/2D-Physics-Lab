#include "focus_engine.h"

// init the engine
void engine_init(FocusEngine *fe, float width, float height)
{
	fe->width = width;
	fe->height = height; 

	fe->window = NULL;
	fe->renderer = NULL; 

	fe->running = false;
	fe->offsetx = 0.0;
	fe->offsety = 0.0; 
	fe->scale = 40.0;

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

	input_init(&fe->input);


	fe->running = true;
}

// destroy the engine
void engine_destroy(FocusEngine *fe)
{
	fe->running = false; 
	SDL_DestroyRenderer(fe->renderer); 
	SDL_DestroyWindow(fe->window);
	SDL_Quit();
}


// convert x coordinate to screen coordinate
float coordx_to_screenx(FocusEngine *fe, float x)
{
	return fe->width/2 + fe->offsetx + (x * fe->scale);
}


// convert y coordinate to screen coordinate
float coordy_to_screeny(FocusEngine *fe, float y)
{
	return fe->height/2 + fe->offsety - (y * fe->scale);
}

// convert screen x coordinate back to world coordinate
float screenx_to_coordx(FocusEngine *fe, int x)
{
    return (x - (fe->width / 2.0f) - fe->offsetx) / fe->scale;
}

// convert screen y coordinate back to world coordinate
float screeny_to_coordy(FocusEngine *fe, int y)
{
    return ((fe->height / 2.0f) + fe->offsety - y) / fe->scale;
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

	// origin : blue.
	// The origin is a circle, so we have to draw every pixel of the area. 
	int r = 5; // 5px radius
    Color c = {255, 255, 0, 255};
	draw_circle(fe, coordx_to_screenx(fe, 0.0), coordy_to_screeny(fe, 0.0), r, c);	

	// set the color back to black
	SDL_SetRenderDrawColor(fe->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}


// draw a circle
void draw_circle(FocusEngine *fe, float xc, float yc, float r, Color c)
{
	SDL_SetRenderDrawColor(fe->renderer, c.r, c.g, c.b, c.a);
	int i, j;
	
	for ( i = xc-r; i < xc + r; i++ )
	{
		for( j = yc-r; j < yc + r; j++)
		{
			if( pow((i-xc), 2) + pow((j-yc), 2) <= r * r )
				SDL_RenderDrawPoint(fe->renderer, i, j);
		}
	}
}


// drawing a vector
void draw_vector(FocusEngine *fe, AppliedVector2D v, Color c)
{
	SDL_SetRenderDrawColor(fe->renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawLine(fe->renderer, coordx_to_screenx(fe, v.origin.x), coordy_to_screeny(fe, v.origin.y), 
                                    coordx_to_screenx(fe, v.end.x), coordy_to_screeny(fe, v.end.y));
}


// start the drawing frame
void start_frame(FocusEngine *fe)
{
    SDL_SetRenderDrawColor(fe->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(fe->renderer);
}


// end the drawing frame
void end_frame(FocusEngine *fe)
{
    SDL_RenderPresent(fe->renderer);
}