
#include <SDL2/SDL_ttf.h>
#include <assert.h>
#include <cstdlib>
#include <iostream>
#include "Render.hpp"

using namespace std;

namespace mango
{


TTF_Font* LoadFont(const char *path, int ptsize)
{
	TTF_Font *f;
	f = TTF_OpenFont(path, ptsize);
	if (f == NULL)
	{
		cout << "Could not load font: " << TTF_GetError() << endl;
		exit(EXIT_FAILURE);
	}

	return (f);
}


}
