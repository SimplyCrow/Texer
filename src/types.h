#pragma once
#include <stdlib.h>

struct TEX_TextureItem
{
        const char *path;
        size_t width;
        size_t height;
        struct SDL_Surface *surface;
        struct SDL_Texture *texture;

        size_t ref_count; // TODO
};
