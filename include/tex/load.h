#pragma once
#include <SDL3/SDL.h>

struct SDLImageInfos
{
	int width;
	int height;
	SDL_Surface *surface;
};

const struct SDLImageInfos invalid_sdl_image_infos = {-1, -1, NULL};

extern struct SDLImageInfos load_surface(const char *path);
