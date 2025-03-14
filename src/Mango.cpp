#include "Mango.hpp"
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>



namespace mango
{

// Editor starts here
Editor* Editor::editor = NULL;

Editor::Editor():View(bg,rect) {

	this->fg = (SDL_Color){
				.r = 225,
				.g = 245,
				.b = 225,
				.a = 255
	};

	this->rect = (SDL_Rect){
		.x=0,.y=0,.h=60
	};

	this->cursor = (SDL_Rect){
		.x=0,.y=0,.w=10,.h=60
	};
}

Editor* Editor::get()
{
	if (editor == NULL)
		editor = new Editor();

	return editor;
}

void Editor::process_events(SDL_Event *e)
{
	if (e->type == SDL_MOUSEWHEEL_NORMAL)
	{
	}

	if (e->type == SDL_MOUSEWHEEL_FLIPPED)
	{
	}
}

void Editor::render(SDL_Renderer *ren)
{
	extern TTF_Font *f;
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
}

// Editor ends here

// Header starts here

Header::Header():View() {

}

// Header ends here

} // namespace mango
