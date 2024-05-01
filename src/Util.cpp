
#include <SDL2/SDL_ttf.h>
#include "Util.hpp"
#include <assert.h>


namespace mango
{

TTF_Font *f;

void init(SDL_Renderer* ren)
{
	LoadFont();
}

void LoadFont()
{
	extern TTF_Font *f;
	f = TTF_OpenFont("./font/FiraMonoNerdFont-Medium.otf", 32);
	assert(f != NULL);
}


}
