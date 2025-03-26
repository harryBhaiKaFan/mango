#ifndef __MANGO_VIEW_HPP__
#define __MANGO_VIEW_HPP__

#include <SDL2/SDL.h>
#include <cstdint>
#include <stdbool.h>

namespace mango
{

	class View
	{
		protected:
			SDL_Rect rect;
			SDL_Rect renderRect;
			SDL_Color bgColor;
			SDL_Color borderColor;
			bool bordered = false;

		public:
			int paddingL = 0;
			int paddingT = 0;
			int paddingR = 0;
			int paddingB = 0;
			
			View(SDL_Color bgColor,SDL_Rect rect);
			void set_border(SDL_Color borderColor);
			void remove_border();
			void padding(uint32_t p);
			void padding_block(uint32_t p);
			void padding_inline(uint32_t p);
			void render(SDL_Renderer *ren);
	};


} // namespace mango

#endif
