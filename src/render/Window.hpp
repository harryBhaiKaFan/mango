#ifndef __MANGO_WINDOW_HPP__
#define __MANGO_WINDOW_HPP__

#include <SDL2/SDL_video.h>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

using namespace std;

namespace mango
{

	class Window
	{
		public:
			SDL_Window* window;
			SDL_Renderer *renderer;
			static Window* win;
		private:

			Window();

		public:
			static Window* get();
			void clear();
			void render();
			~Window();
	};

}

#endif
