#include <tex/load.h>
#include <munit.h>
#include <SDL3/SDL.h>

MunitResult test0(const MunitParameter params[], void *user_data_or_fixture)
{
	const char* first;
	const char* second;

	first = munit_parameters_get(params, "first");
	second = munit_parameters_get(params, "second");

	if (strlen(first) + strlen(second) != 8) {
		munit_assert_int(strlen(first) + strlen(second), ==, 6);
		return MUNIT_FAIL;
	}

	return MUNIT_OK;
}

int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_VIDEO);


	SDL_Window* window = SDL_CreateWindow("Image", 600, 800, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0);

	struct SDLImageInfos image = load_surface("demo1.png");
	struct SDLImageInfos image_demo = load_surface("demo2.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image.surface);
	SDL_Texture* texture_1 = SDL_CreateTextureFromSurface(renderer, image_demo.surface);

	bool quit = false;
	while (!quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT)
				quit = true;
		}

		SDL_SetRenderDrawColor(renderer, 0x20, 0x20, 0x20, 0xff);
		SDL_RenderClear(renderer);
		SDL_FRect rect = {.w = 300, .h=800, .x=0, .y=0};
		SDL_FRect rect2 = {.w = 300, .h=800, .x=300, .y=0};
		SDL_RenderTexture(renderer, texture, NULL, &rect);
		SDL_RenderTexture(renderer, texture_1, NULL, &rect2);
		SDL_RenderPresent(renderer);
	}

	return 0;
	char *test0_params0[] = {
		"one", "two", "three", NULL
	};

	char *test0_params1[] = {
		"red", "green", "blue", NULL
	};

	MunitParameterEnum test_params[] = {
		{"first", test0_params0},
		{"second", test0_params1},
		{NULL, NULL}
	};

	MunitTest tests[] = {
		{
			"/test0",
			test0,
			NULL,
			NULL,
			MUNIT_TEST_OPTION_NONE,
			test_params
		},
		{NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
	};

	MunitSuite suite = {
		"/tests",
		tests,
		NULL,
		1,
		MUNIT_SUITE_OPTION_NONE
	};

	return munit_suite_main(&suite, NULL, argc, argv);
}
