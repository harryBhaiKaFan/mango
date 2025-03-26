#ifndef __MANGO_TEXT_INPUT_HPP__
#define __MANGO_TEXT_INPUT_HPP__

#include "View.hpp"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_ttf.h>
#include <cstdint>
#include <string>
using namespace std;

namespace mango
{

class TextInput: public View
{
	private:
		SDL_Rect cursor_rect;
		SDL_Rect textRect;
		SDL_Color fgColor;
		int text_st_pos = 0;
		int text_count = 0;
		int cursor_pos = 0;
		string text = "";
		bool input_on = false;
		int prev_time = 0;
		uint8_t cursor_opacity = 0;
		bool pending_shift = false;
		TTF_Font *font = NULL;
		const string allowed_char = "1234567890abcdefghijklmnopqrstuvwxyz`-=[]\\;',./ ";
		const string allowed_shift_char = "!@#$%^&*()ABCDEFGHIJKLMNOPQRSTUVWXYZ~_+{}|:\"<>? ";
	public:
		TextInput(const char *font_path,SDL_Rect rect,SDL_Color bgColor,SDL_Color fgColor,int padding);
		void set_y(uint32_t y);
		void start_input();
		void stop_input();
		string get_text();
		void set_text(string str);
		void set_font(const char *font_path);
		void process_events(SDL_Event *e);
		void render(SDL_Renderer *ren);
};

} // namespace mangp

#endif
