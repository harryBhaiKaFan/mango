#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "Window.hpp"
#include "Editor.hpp"
#include "Util.hpp"

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
	mango::Editor* editor = mango::Editor::get();

	mango::init(win->renderer);

	SDL_Event e;
	bool running = true;

	SDL_StartTextInput(); // For android
	while(running)
	{
		while(SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				case SDL_QUIT:
					running = false;
					break;

				case SDL_KEYUP:
					editor->keydown = false;
					break;

				case SDL_KEYDOWN:
					editor->cursorA = 255;
					editor->keydown = true;
					int ch = e.key.keysym.sym;

					if(ch == 8 && editor->text.size() > 0)
						editor->text.pop_back();
					else if(isalnum(ch) || ispunct(ch) || ch == 32)
						editor->text.push_back((char)ch);

					break;
			}
			win->clear();
			editor->render(win->renderer);
			win->render();
		}



		SDL_Delay(17);
	}


	SDL_Quit();
	return (EXIT_SUCCESS);
}
