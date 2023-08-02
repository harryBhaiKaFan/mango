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


	SDL_Window *win = SDL_CreateWindow("Mango",0,0,640,480,SDL_WINDOW_SHOWN);
	SDL_Renderer *ren = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

	if (ren == NULL)
	{
		cout << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}

	TTF_Font *f = TTF_OpenFont("./font/FiraMonoNerdFont-Regular.otf", 32);
	SDL_Event e;
	bool running = true,keydown = false;
	string text = "";
	SDL_Color fg = {
		.r = 225,
		.g = 245,
		.b = 225,
		.a = 255
	};
	SDL_Rect rect = {
		.x=0,.y=0,.h=60
	};

	SDL_Rect cursor = {
		.x=0,.y=0,.w=10,.h=60
	};
	int cursorA = 255;
	uint32_t lp = 0;
	uint32_t cp = 0;

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
					keydown = false;
					break;

				case SDL_KEYDOWN:
					cursorA = 255;
					keydown = true;
					int ch = e.key.keysym.sym;

					if(ch == 8 && text.size() > 0)
						text.pop_back();
					else if(isalnum(ch) || ispunct(ch) || ch == 32)
						text.push_back((char)ch);

					break;
			}
		}

		SDL_SetRenderDrawColor(ren,30,30,30,255);
		SDL_RenderClear(ren);

		SDL_Surface *surf = TTF_RenderText_Solid(f,text.c_str(),fg);
		SDL_Texture *tex = SDL_CreateTextureFromSurface(ren,surf);

		if (text.size()*25 < 640)
			rect.w = text.size()*25;

		cursor.x = rect.w + 3;

		SDL_RenderCopy(ren,tex,NULL,&rect);


		if ((lp == 0 || cp - lp >= 600) && !keydown)
		{
			lp = SDL_GetTicks();
			if (cursorA == 255)
				cursorA = 0;
			else 
				cursorA = 255;
		}


		SDL_SetRenderDrawColor(ren,120,230,120,cursorA);
		SDL_RenderFillRect(ren,&cursor);

		cp = SDL_GetTicks();

		SDL_RenderPresent(ren);
		SDL_Delay(17);
	}


	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return (EXIT_SUCCESS);
}
