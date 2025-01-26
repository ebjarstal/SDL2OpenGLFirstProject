#include <SDL.h>
#include <iostream>

#define W_WIDTH 1280
#define W_HEIGHT 720

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

	SDL_Surface* image = SDL_LoadBMP("./cars.bmp");
	SDL_BlitSurface(image, nullptr, surface, nullptr);
	SDL_FreeSurface(image);
	SDL_UpdateWindowSurface(window);

	bool is_running = true;
	while (is_running) {

		SDL_Event event;
		// Queue of events to handle
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) is_running = false;
			if (event.type == SDL_KEYDOWN) {
				// scancode: physical key
				// sym: virtual key
				// Usage depends on purpose of program: is the keyboard layout important?
				if (event.key.keysym.sym == SDLK_LEFT) std::cout << "left arrow down\n";
			}
			// get an array of which the length is the number of existing scancodes
			// array[key_scancode] is 0 when key is not pressed, 1 when pressed
			const Uint8* kb_state = SDL_GetKeyboardState(nullptr);
			if (kb_state[SDL_SCANCODE_F] == 1) std::cout << "f key down\n";
		}

	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}