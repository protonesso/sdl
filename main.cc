#include <SDL2/SDL.h>

SDL_Window *sk_window = NULL;
SDL_Surface *sk_surface, *sk_surface2 = NULL;

static void msg(const char *msg, ...) {
	printf("INFO: %s\n", msg);
}

static bool init() {
	msg("Stating init()");

	msg("Checking SDL_INIT_VIDEO");
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Failed to load SDL: %s", SDL_GetError());
		return false;
	}

	msg("Creating SDL window");
	sk_window = SDL_CreateWindow("Skvizzgard test", 100, 100, 600, 591, SDL_WINDOW_SHOWN);
	if (sk_window == NULL) {
		fprintf(stderr, "Failed to open *sk_window: %s", SDL_GetError());
		return false;
	}

	msg("Creating window surface");
	sk_surface2 = SDL_GetWindowSurface(sk_window);

	return true;
}

static bool media_load() {
	msg("Opening 1.bmp");
	sk_surface = SDL_LoadBMP("1.bmp");
	if (sk_surface == NULL) {
		fprintf(stderr, "Failed to load image: %s", SDL_GetError());
		return false;
	}

	return true;
}

static void close() {
	msg("Closing surface");
	SDL_FreeSurface(sk_surface);
	msg("Destroying window");
	SDL_DestroyWindow(sk_window);
	msg("Exiting...");
	SDL_Quit();
}

int main() {
	init();
	media_load();
	msg("Doing some stuff");
	SDL_BlitSurface(sk_surface, NULL, sk_surface2, NULL);
	SDL_UpdateWindowSurface(sk_window);
	SDL_Delay(10000);
	close();
	return 0;
}
