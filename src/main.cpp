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


#include "Mango.hpp"
#include "render/Window.hpp"

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


	mango::Window* win = mango::Window::get();

	mango::Header *header = mango::Header::get(win->renderer);
	mango::TabNav *tabnav = mango::TabNav::get(win->renderer);
	mango::Editor *editor = mango::Editor::get(win->renderer);

	SDL_Event e;
	bool running = true;

	while(running)
	{
		while(SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
			}

			header->process_events(&e);
			tabnav->process_events(&e);
			editor->process_events(&e);
		}
		win->clear();

		tabnav->render(win->renderer);
		editor->render(win->renderer);
		header->render(win->renderer);

		win->render();
		SDL_Delay(17);
	}


	SDL_Quit();
	return (EXIT_SUCCESS);
}
