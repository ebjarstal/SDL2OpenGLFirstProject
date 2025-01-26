#include <SDL.h>
#include <glad/glad.h>
#include <iostream>

#define W_WIDTH 1280
#define W_HEIGHT 720

int main(int argc, char* argv[]) {

	SDL_Window*  window  = nullptr;
	SDL_Surface* surface = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL video system initialization: FAIL\n" << SDL_GetError() << "\n";
	}
	else {
		std::cout << "SDL video system initialization: OK\n";
	}

	// before creating window, specify OpenGL version (4.1) and setup context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_WIDTH, W_HEIGHT, 
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (!window) {
		std::cout << "SDL window creation: FAIL\n";
		return 1;
	}

	// setup OpenGL context
	SDL_GLContext context;
	context = SDL_GL_CreateContext(window);

	// setup function pointers
	gladLoadGLLoader(SDL_GL_GetProcAddress);

	bool is_running = true;
	while (is_running) {
		glViewport(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_WIDTH, W_HEIGHT);

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

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);

	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}