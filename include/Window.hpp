#ifndef __MANGO_WINDOW_HPP__
#define __MANGO_WINDOW_HPP__

#include <SDL2/SDL_video.h>
#include <cstdlib>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

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


			Window()
			{

				this->window = SDL_CreateWindow("Mango",0,0,640,480,SDL_WINDOW_SHOWN);
				this->renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

				if (renderer == NULL)
				{
					cout << SDL_GetError() << endl;
					exit(EXIT_FAILURE);
				}
			}
		public:

			static Window* get()
			{
				if (win == NULL)
					win = new Window();

				return win;
			}
			void clear()
			{
				SDL_SetRenderDrawColor(renderer,30,30,30,255);
				SDL_RenderClear(renderer);
			}
			void render()
			{
				SDL_RenderPresent(renderer);
			}
			~Window()
			{
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
			}

	};

}

#endif
