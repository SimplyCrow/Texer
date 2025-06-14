#include <tex/texer.h>
#include <tex/error.h>
#include <SDL3/SDL.h>
#include <stddef.h>
#include <stdlib.h>

#include "common.h"
#include "types.h"

struct TEX_TextureHandler
{
        size_t index;
};

// Main storage
struct TEX_TexerManager
{
        size_t capacity;
        size_t first_free_slot;         // index of first free slot
        struct TEX_TextureItem *items;
};

struct TEX_TexerManager *TEX_CreateTexerManager(const size_t capacity)
{
        struct TEX_TexerManager *manager =
                malloc(sizeof(struct TEX_TexerManager));
                        
        if(TEX_ErrorMalloc(manager))
                return NULL;
        
        manager->capacity = capacity;
        manager->first_free_slot = 0;
        manager->items = calloc(capacity, sizeof(struct TEX_TextureItem));

        if(TEX_ErrorMalloc(manager->items))
                return NULL;
        
        return manager;
}

struct TEX_TextureHandler TEX_LoadTexture(const char* path)
{
        todo("LoadTexture");
        struct TEX_TextureHandler t = {0};
        return t;
}

struct SDL_Surface* TEX_GetSurface()
{
        return todo_ptr("GetSurface");
}

struct SDL_Texture* TEX_GetTexture()
{
        return todo_ptr("GetTexture");
}
