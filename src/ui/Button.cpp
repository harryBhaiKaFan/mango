#include "Button.hpp"
#include "TextView.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <cstddef>


namespace mango
{

Button::Button(const char *btn_txt,SDL_Renderer *ren,SDL_Rect rect,const char *font_path,SDL_Color bgColor={25,25,25,255},SDL_Color fgColor={255,255,255,255},int padding = 10):
	View(bgColor,rect),
	btnText(btn_txt, font_path,ren,(SDL_Color){0},fgColor, rect, TEXT_ALIGN_CENTER)
{
	this->padding(padding);
}

void Button::attach_click_listener(void* (*fn)(void*))
{
	this->on_click = fn;
}

void Button::detach_click_listener()
{
	this->on_click = NULL;
}

void Button::process_events(SDL_Event *e)
{
	int mx = -1, my = -1,click = 0;

	click = SDL_GetMouseState(&mx, &my);

	if (mx > this->renderRect.x && mx < this->renderRect.x + this->renderRect.w && my > this->renderRect.y && my < this->renderRect.y + this->renderRect.h)
	{
		if (click && this->on_click != NULL)
			click_return_data = on_click(click_param_data);
	}
}

void Button::render(SDL_Renderer *ren)
{
	((View*)this)->render(ren);
	btnText.render(ren);
}

} // namespace mango
