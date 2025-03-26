#include "View.hpp"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <cstdint>

namespace mango
{

View::View(SDL_Color bgColor, SDL_Rect rect)
{
	this->bgColor = bgColor;
	this->rect = rect;
	this->renderRect = rect;
}

void View::set_border(SDL_Color borderColor)
{
	bordered = true;
	this->borderColor = borderColor;
}

void View::remove_border()
{
	bordered = false;
}

void View::padding(uint32_t p)
{
	padding_block(p);
	padding_inline(p);
}

void View::padding_block(uint32_t p)
{
	paddingT = p;
	paddingB = p;
}

void View::padding_inline(uint32_t p)
{
	paddingL = p;
	paddingR = p;
}

void View::render(SDL_Renderer *ren)
{
	renderRect = {
		.x = rect.x - paddingL,
		.y = rect.y - paddingT,
		.w = rect.w + 2*paddingR,
		.h = rect.h + 2*paddingB
	};

	SDL_SetRenderDrawColor(ren, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	SDL_RenderFillRect(ren,&renderRect);

	if (bordered)
	{
		SDL_SetRenderDrawColor(ren,borderColor.r,borderColor.g,borderColor.b,borderColor.a);
		SDL_RenderDrawRect(ren, &renderRect);
	}
}

} // namespace mango
