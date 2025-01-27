#include <SDL.h>
#include <iostream>

#define W_WIDTH 1280
#define W_HEIGHT 720

void PaintPixel(SDL_Surface* surface, uint8_t r, uint8_t g, uint8_t b) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	uint8_t* pixels = (uint8_t*) surface->pixels;
	pixels[y * surface->pitch + x * surface->format->BytesPerPixel + 0] = b;
	pixels[y * surface->pitch + x * surface->format->BytesPerPixel + 1] = g;
	pixels[y * surface->pitch + x * surface->format->BytesPerPixel + 2] = r;
}

int main(int argc, char* argv[]) {

	SDL_Window*  window  = nullptr;
	SDL_Surface* surface = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL video system initialization: FAIL\n" << SDL_GetError() << "\n";
	}

	window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_WIDTH, W_HEIGHT, 
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (!window) {
		std::cout << "SDL window creation: FAIL\n";
		return 1;
	}
	
	surface = SDL_GetWindowSurface(window);
	if (!surface) {
		std::cout << "SDL window surface fetch: FAIL\n";
	}

	std::cout << "Press 'r' for red, 'g' for green, and 'b' for blue. Press mouse left button to paint.\n";
	uint8_t r = 0x00, g = 0x00, b = 0x00;

	bool is_running = true;
	while (is_running) {

		SDL_Event event;
		// Queue of events to handle
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) is_running = false;
			if (event.type == SDL_KEYDOWN) {
				// TODO: make red mode by default
				if (event.key.keysym.sym == SDLK_r) {
					std::cout << "Color set to 'red'\n";
					r = 0xff; g = 0x00; b = 0x00;
				}
				if (event.key.keysym.sym == SDLK_g) {
					std::cout << "Color set to 'green'\n";
					r = 0x00; g = 0xff; b = 0x00;
				}
				if (event.key.keysym.sym == SDLK_b) {
					std::cout << "Color set to 'blue'\n";
					r = 0x00; g = 0x00; b = 0xff;
				}
			}
			if (event.button.button == SDL_BUTTON_LEFT) {
				PaintPixel(surface, r, g, b);
			}
		}

		SDL_UpdateWindowSurface(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}