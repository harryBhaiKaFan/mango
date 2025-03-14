
#include <SDL2/SDL_ttf.h>
#include <assert.h>
#include <cstdlib>
#include <iostream>
#include "Render.hpp"

using namespace std;

namespace mango
{


void init(SDL_Renderer* ren)
{
	// TODO: app init fn
}

TTF_Font* LoadFont(const char *path)
{
	TTF_Font *f;
	f = TTF_OpenFont(path, 72);
	if (f == NULL)
	{
		cout << "Could not load font: " << TTF_GetError() << endl;
		exit(EXIT_FAILURE);
	}

	return (f);
}


}
