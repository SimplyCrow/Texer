#pragma once
#include <SDL3/SDL.h>

#include "types.h"
extern int TEX_LoadTextureFromMemory(   const char* path, 
                                        struct SDL_Renderer* renderer,
                                        struct TEX_TextureItem* item);
