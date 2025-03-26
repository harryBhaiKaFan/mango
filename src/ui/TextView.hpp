#ifndef __MANGO_TEXTVIEW_HPP__
#define __MANGO_TEXTVIEW_HPP__

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_ttf.h>
#include <cstdint>
#include "View.hpp"

namespace mango
{
typedef enum{
	TEXT_ALIGN_LEFT,
	TEXT_ALIGN_CENTER,
	TEXT_ALIGN_RIGHT
}Text_Alignment;

class TextView: public View
{
	private:
		SDL_Texture *text_tx;
		SDL_Rect textRect;
	public:
		TextView(const char *text,const char *font_path,SDL_Renderer *ren,SDL_Color bgColor,SDL_Color fgColor,SDL_Rect rect,Text_Alignment talgn);
		static SDL_Texture* LoadText(const char *text,TTF_Font* font,SDL_Renderer* ren,SDL_Color color);
		void set_y(uint32_t y);
		void render(SDL_Renderer *ren);
};

} // namespace mango

#endif
