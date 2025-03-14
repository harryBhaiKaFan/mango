#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


// TODO:
// 
// 1. Implement window and rendering system properly
// 2. init() fn must initialise app
// 		i. Mango.hpp and Mango.cpp will have the functional of app
// 3. assembling components and making the app

#include "render/Window.hpp"
#include "render/Render.hpp"

using namespace std;

int main(int ac,char *av[])
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << SDL_GetError() << endl;
		exit(EXIT_FAILURE);
	}

	if (TTF_Init() != 0)
	{
		cout << SDL_GetError() << endl;
		exit(EXIT_FAILURE);
	}

	TTF_Font *f = mango::LoadFont("./font/FiraMonoNerdFontMono-Medium.otf");

	mango::Window* win = mango::Window::get();
	mango::init(win->renderer);


	SDL_Event e;
	bool running = true;

	SDL_StartTextInput(); // For android
	while(running)
	{
		while(SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
			}

		}


		win->clear();

		win->render();

		SDL_Delay(17);
	}


	SDL_Quit();
	return (EXIT_SUCCESS);
}
