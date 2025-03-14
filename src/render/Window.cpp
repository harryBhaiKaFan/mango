#include "Window.hpp"
#include <iostream>

using namespace std;

namespace mango
{

Window* Window::win = NULL;

Window::Window()
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


Window* Window::get()
{
	if (win == NULL)
		win = new Window();

	return win;
}

void Window::clear()
{
	SDL_SetRenderDrawColor(renderer,30,30,30,255);
	SDL_RenderClear(renderer);
}
void Window::render()
{
	SDL_RenderPresent(renderer);
}

Window::~Window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}


} // namespace mango
