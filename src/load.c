#include "tex/load.h"

#include <SDL3/SDL.h>
#include <ctype.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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



void hex_dump_file(const struct FileInfos infos)
{
	const size_t rows = infos.file_size / 16 + 1;
	const size_t elements_in_last_row = infos.file_size % 16;
	const size_t max_rows = 1000000;
	for (int i = 0; i < rows && i < max_rows; ++i) {
		size_t cols = 16;
		if (i == rows - 1)
			cols = elements_in_last_row;

		printf("0x%08x: ", 16 * i);
		for (int j = 0; j < cols; ++j) {
			printf("0x%02x ", infos.data[16 * i + j]);
		}

		for (int j = 0; j < 16 - cols; ++j) {
			printf("     ");
		}

		for (int j = 0; j < cols; ++j) {
			printf("%c",
			       isprint(infos.data[16 * i + j])
				       ? (char)infos.data[16 * i + j]
				       : '.');
		}

		printf("\n");
	}
}

SDL_PixelFormat get_pixel_format_from_stbi(int stbi_code)
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

int get_number_of_bytes_per_pixel_stbi(int stbi_code)
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

bool open_file(const char *path, struct FileInfos *infos)
{
	infos->data = (uint8_t *)SDL_LoadFile(path, &infos->file_size);
	if (infos->data == NULL)
		return false;
	return true;
}

struct ImageInfos load_image(const char *path)
{
	struct FileInfos file_info;
	if (!open_file(path, &file_info)) {
		SDL_Log("ERROR: Tried to load image: %s", SDL_GetError());
		return invalid_image_infos;
	}

	struct ImageInfos image_infos;
	image_infos.data = stbi_load_from_memory(file_info.data,
	                                         (int)file_info.file_size,
	                                         &image_infos.width,
	                                         &image_infos.height,
	                                         &image_infos.color_channel,
	                                         STBI_default);
	return image_infos;
}

struct SDLImageInfos load_surface(const char *path)
{
	struct SDLImageInfos surface_infos;
	const struct ImageInfos image_infos = load_image(path);

	if (image_infos.data == NULL) {

	SDL_Log("ERROR: Tried to load image from memory: %s",
		stbi_failure_reason());
		return invalid_sdl_image_infos;
	}

	surface_infos.width = image_infos.width;
	surface_infos.height = image_infos.height;

	const int pixel_format = get_pixel_format_from_stbi(
		image_infos.color_channel);
	const int byte_per_pixel = get_number_of_bytes_per_pixel_stbi(
		image_infos.color_channel);
	const int pitch = byte_per_pixel * image_infos.width;

	surface_infos.surface = SDL_CreateSurfaceFrom(
		image_infos.width,
		image_infos.height,
		pixel_format,
		image_infos.data,
		pitch
		);

	if (surface_infos.surface == NULL) {

		SDL_Log("ERROR: Tried to create surface: %s",
			SDL_GetError());
		return invalid_sdl_image_infos;
	}

	return surface_infos;
}