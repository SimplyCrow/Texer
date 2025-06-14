#include "load.h"
#include <tex/error.h>

#include <SDL3/SDL.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "types.h"

struct FileInfos
{
	size_t file_size;
	uint8_t *data;
};

const struct FileInfos invalid_file_info = {-1, NULL};

struct ImageInfos
{
	int width;
	int height;
	int color_channel;
	uint8_t *data;
};

const struct ImageInfos invalid_image_infos = {-1, -1, -1, NULL};

// stbi pixel format to sdl
SDL_PixelFormat TEX_STBIPixelFormat(int stbi_code)
{
	switch (stbi_code) {
	default:
	case STBI_default:
	case STBI_grey:
	case STBI_grey_alpha:
		return SDL_PIXELFORMAT_UNKNOWN;
	case STBI_rgb:
		return SDL_PIXELFORMAT_RGB24;
	case STBI_rgb_alpha:
		return SDL_PIXELFORMAT_RGBA32;
	}
}

// number of bytes per pixel from stbi
int TEX_NumberOfBytes(int stbi_code)
{
	switch (stbi_code) {
	default:
	case STBI_default:
	case STBI_grey:
	case STBI_grey_alpha:
		return -1;
	case STBI_rgb:
		return 3;
	case STBI_rgb_alpha:
		return 4;
	}
}

int TEX_OpenFile(const char *path, struct FileInfos *infos)
{
	infos->data = (uint8_t *)SDL_LoadFile(path, &infos->file_size);
	if (infos->data == NULL)
        {
                TEX_RaiseErrorSDL(TEX_SDL_NO_FILE);                
		return false;
        }
	return true;
}

int TEX_LoadImage(const char *path, struct ImageInfos* image_infos)
{
	struct FileInfos file_info;
	if (!TEX_OpenFile(path, &file_info)) {
		return false;
	}

	image_infos->data = stbi_load_from_memory(file_info.data,
	                                         (int)file_info.file_size,
	                                         &image_infos->width,
	                                         &image_infos->height,
	                                         &image_infos->color_channel,
	                                         STBI_default);
        if(image_infos->data == NULL)  {
                TEX_RaiseErrorDetailed(TEX_STBI, stbi_failure_reason());
                return false;
        }

	return true;
}

int TEX_LoadSurface(    const struct ImageInfos image_infos,
                        struct SDL_Surface *surface)
{
        
	const int pixel_format = 
                TEX_STBIPixelFormat(image_infos.color_channel);
	const int byte_per_pixel = 
		TEX_NumberOfBytes(image_infos.color_channel);
        
	const int pitch = byte_per_pixel * image_infos.width;

	surface = SDL_CreateSurfaceFrom(
		image_infos.width,
		image_infos.height,
		pixel_format,
		image_infos.data,
		pitch
		);

	if (surface == NULL) {
                TEX_RaiseErrorSDL(TEX_SDL_SURFACE);
		return false;
	}

	return true;
}

int TEX_LoadTexture(    const struct ImageInfos image_infos,
                        struct SDL_Surface *surface,
                        struct SDL_Renderer *renderer,
                        struct SDL_Texture *texture)
{
        
	const int pixel_format = 
                TEX_STBIPixelFormat(image_infos.color_channel);
	const int byte_per_pixel = 
		TEX_NumberOfBytes(image_infos.color_channel);
        
	const int pitch = byte_per_pixel * image_infos.width;

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL) {
                TEX_RaiseErrorSDL(TEX_SDL_TEXTURE);
		return false;
	}

	return true;
}

int TEX_LoadTextureFromMemory(          const char* path, 
                                        struct SDL_Renderer* renderer,
                                        struct TEX_TextureItem* item)
{
        struct ImageInfos image_infos;
        if(!TEX_LoadImage(path, &image_infos))
            return false;    

        struct SDL_Surface *surface;
        if(!TEX_LoadSurface(image_infos, surface))
                return false;
        
        struct SDL_Texture *texture;
        if(!TEX_LoadTexture(image_infos, surface, renderer, texture))
                return false;

        item->path = path;
        item->width = image_infos.width;
        item->height = image_infos.height;
        item->surface = surface;
        item->texture = texture;
        item->ref_count = 1;
}

