#include <SDL.h>
#include <iostream>
#include <algorithm>

#define W_WIDTH 1280
#define W_HEIGHT 720
#define BRUSH_DEFAULT_SIZE 50

enum CURSOR_MODE {
	ERASER,
	BRUSH
};

void PaintPixel(SDL_Surface* surface, const int x, const int y, const uint8_t r, const uint8_t g, const uint8_t b) {
	uint8_t* pixels = (uint8_t*) surface->pixels;
	if (x > 0 && x < W_WIDTH && y > 0 && y < W_HEIGHT) {
		pixels[y * surface->pitch + x * surface->format->BytesPerPixel + 0] = b;
		pixels[y * surface->pitch + x * surface->format->BytesPerPixel + 1] = g;
		pixels[y * surface->pitch + x * surface->format->BytesPerPixel + 2] = r;
	}
}

void PaintArea(SDL_Surface* surface, const int brush_size, const uint8_t r, const uint8_t g, const uint8_t b) {
	int x, y;
	SDL_GetMouseState(&x, &y);

	uint8_t* pixels = (uint8_t*)surface->pixels;
	for (int col = -brush_size / 2; col < brush_size / 2; col++) {
		for (int row = -brush_size / 2; row < brush_size / 2; row++) {
			PaintPixel(surface, x + col, y + row, r, g, b);
		}
	}
}

int main(int argc, char* argv[]) {

	SDL_Window*  window  = nullptr;
	SDL_Surface* surface = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL video system initialization: FAIL\n" << SDL_GetError() << "\n";
	}

	window = SDL_CreateWindow(
		"SDL2 Window", 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		W_WIDTH, 
		W_HEIGHT, 
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (!window) {
		std::cout << "SDL window creation: FAIL\n";
		return 1;
	}
	
	surface = SDL_GetWindowSurface(window);
	if (!surface) {
		std::cout << "SDL window surface fetch: FAIL\n";
	}

	CURSOR_MODE cursor_mode = BRUSH;
	unsigned int brush_size = BRUSH_DEFAULT_SIZE;
	std::cout << "Press 'r' for red, 'g' for green, 'b' for blue, 'e' for eraser. Press mouse left button to use brush.\n";
	std::cout << "Use mouse wheel to modify size of brush.\n";
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
					std::cout << "Brush set to 'red'\n";
					r = 0xff; g = 0x00; b = 0x00;
					cursor_mode = BRUSH;
				}
				if (event.key.keysym.sym == SDLK_g) {
					std::cout << "Brush set to 'green'\n";
					r = 0x00; g = 0xff; b = 0x00;
					cursor_mode = BRUSH;
				}
				if (event.key.keysym.sym == SDLK_b) {
					std::cout << "Brush set to 'blue'\n";
					r = 0x00; g = 0x00; b = 0xff;
					cursor_mode = BRUSH;
				}
				if (event.key.keysym.sym == SDLK_e) {
					std::cout << "Brush set to 'eraser'\n";
					cursor_mode = ERASER;
				}
			}
			if (event.button.button == SDL_BUTTON_LEFT) {
				if (cursor_mode == BRUSH) PaintArea(surface, brush_size, r, g, b);
				if (cursor_mode == ERASER) PaintArea(surface, brush_size, 0x00, 0x00, 0x00);
			}
			if (event.type == SDL_MOUSEWHEEL) {
				if (event.wheel.y < 0) {
					if (brush_size > 2) brush_size -= 2;
					std::cout << "Brush size decreased to " << brush_size << "\n";
				}
				if (event.wheel.y > 0) {
					if (brush_size < std::max(W_WIDTH, W_HEIGHT)) brush_size += 2;
					std::cout << "Brush size increased to " << brush_size << "\n";
				}
			}
		}

		SDL_UpdateWindowSurface(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}