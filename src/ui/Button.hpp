#ifndef __MANGO_BUTTON_HPP__
#define __MANGO_BUTTON_HPP__

#include "TextView.hpp"
#include "View.hpp"
#include <SDL2/SDL_events.h>
namespace mango
{

class Button: public View
{
	private:
		TextView btnText;
		void*(*on_click)(void*) = NULL;
	public:
		void* click_param_data = NULL;
		void* click_return_data = NULL;

		Button(const char* btn_txt,SDL_Renderer *ren, SDL_Rect rect,const char *font_path, SDL_Color bgColor, SDL_Color fgColor,int padding);

		void attachClickListener(void*(*fn)(void*));
		void detachClickListener(void);
		void process_events(SDL_Event *e);
		void render(SDL_Renderer* ren);
};

} // namespace mango

#endif
