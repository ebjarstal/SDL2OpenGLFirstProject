#include <SDL.h>
#include <iostream>

#define W_WIDTH 1280
#define W_HEIGHT 720

int main(int argc, char* argv[]) {

	SDL_Window*  window  = nullptr;
	SDL_Surface* surface = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL video system initialization: FAIL" << SDL_GetError() << std::endl;
	}
	else {
		std::cout << "SDL video system initialization: OK" << std::endl;
	}

	window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_WIDTH, W_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cout << "SDL window creation: FAIL" << std::endl;
		return 1;
	}

	bool is_running = true;
	while (is_running) {
		SDL_Event event;
		// Queue of events to handle
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) is_running = false;
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}