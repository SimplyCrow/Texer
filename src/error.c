#include <tex/error.h>
#include <stdio.h>
#include <SDL3/SDL.h>

size_t tex_errno = 0;
const char *tex_errstr = "";

const char* TEX_GetError()
{
        switch(tex_errno)
        {
        default:
        case 0:
                return "\0";
        case TEX_OUT_OF_MEMORY:
                return "Memory allocation failed (OUT OF MEMORY)";
        case TEX_SDL_NO_FILE:
                return "SDL could not open file (SDL NO FILE)";
        case TEX_SDL_SURFACE:
                return "SDL could create surface (SDL SURFACE)";
        case TEX_SDL_TEXTURE:
                return "SDL could create texture (SDL TEXTURE)";
        case TEX_STBI:
                return "STBI image loader had an error (STBI)";
        }
}

const char* TEX_GetDetails()
{
        return tex_errstr;
}

void TEX_RaiseError(const size_t code)
{
        tex_errstr = NULL;
        tex_errno = code;
}

void TEX_RaiseErrorDetailed(const size_t code, const char* str)
{
        tex_errstr = str;
        tex_errno = code;
}

void TEX_RaiseErrorSDL(const size_t code)
{
        TEX_RaiseErrorDetailed(code, SDL_GetError());
}

int TEX_ErrorMalloc(const void* pointer)
{
        if(pointer == NULL)
                TEX_RaiseError(TEX_OUT_OF_MEMORY);
        return pointer == NULL;
}
