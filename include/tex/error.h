#include <stdio.h>

enum {
        TEX_OUT_OF_MEMORY = 1,
        TEX_SDL_NO_FILE,
        TEX_SDL_SURFACE,
        TEX_SDL_TEXTURE,
        TEX_STBI
};

extern const char* TEX_GetError();
extern const char* TEX_GetDetails();
extern void TEX_RaiseError(const size_t code);
extern void TEX_RaiseErrorDetailed(const size_t code, const char* str);
extern void TEX_RaiseErrorSDL(const size_t code);
extern int TEX_ErrorMalloc(const void* pointer);
