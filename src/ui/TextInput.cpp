#include "TextInput.hpp"
#include "TextView.hpp"
#include "View.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <cstddef>
using namespace std;

namespace mango
{

TextInput::TextInput(const char *font_path,SDL_Rect rect,SDL_Color bgColor,SDL_Color fgColor={255,255,255,255},int padding = 10):View(bgColor,rect)
{
	this->padding(padding);
	this->fgColor = fgColor;
	this->textRect = rect;
	this->cursor_rect = (SDL_Rect){
		.x = textRect.x,
		.y = textRect.y,
		.w = 2,
		.h = textRect.h
	};
	set_font(font_path);
}

void TextInput::set_y(uint32_t y)
{
	this->rect.y = y;
	this->textRect.y = y;
	this->cursor_rect.y = y;
}

void TextInput::start_input()
{
	set_border({255,255,0,255});
	SDL_GetKeyboardFocus();
	SDL_StartTextInput();
	input_on = true;
}

void TextInput::stop_input()
{
	SDL_StopTextInput();
	remove_border();
	input_on = false;
}

string TextInput::get_text()
{
	return text; 
}

void TextInput::set_text(string str)
{
	text = str;
}

void TextInput::set_font(const char *font_path)
{
	this->font = TTF_OpenFont(font_path, 0.75 * textRect.h);
}

void TextInput::process_events(SDL_Event *e)
{
	if (e->type == SDL_KEYDOWN && input_on)
	{
		int64_t ch = e->key.keysym.sym;
		int extent;

		size_t ch_pos = string::npos;
		if ((ch_pos=allowed_char.find(ch)) != string::npos)
		{
			if (pending_shift)
			{
				ch = allowed_shift_char[ch_pos];
			}

			text.insert(text.begin() + cursor_pos,ch);
			cursor_pos++;
		}else if(ch == SDLK_LSHIFT || ch == SDLK_RSHIFT)
		{
			pending_shift = true;
		}else if(ch == SDLK_LEFT)
		{
			if (cursor_pos > 0)
				cursor_pos--;
		} else if(ch == SDLK_RIGHT)
		{
			if (cursor_pos < text.size())
				cursor_pos++;
		} else if(ch == SDLK_BACKSPACE)
		{
			if (cursor_pos > 0)
			{
				text.erase(cursor_pos-1,1);
				cursor_pos--;
				if (text_st_pos > 0) text_st_pos--;
			}
		}else{
			return; // TODO: handle the rest of the keys too
		}

		textRect.w = rect.w;
		TTF_MeasureText(font,text.c_str(),textRect.w, &extent, &text_count);

		if (textRect.w > extent) textRect.w = extent;
		if (cursor_pos > text_st_pos + text_count)
		{
			text_st_pos++;
		} else if (cursor_pos < text_st_pos)
		{
			text_st_pos--;
		}

	} else if (e->type == SDL_KEYUP)
	{
		if (e->key.keysym.sym == SDLK_LSHIFT || e->key.keysym.sym == SDLK_RSHIFT)
		{
			pending_shift = false;
		}
	}else if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		int mx,my,click;
		click = SDL_GetMouseState(&mx, &my);

		if (!(mx > this->renderRect.x && mx < this->renderRect.x + this->renderRect.w && my > this->renderRect.y && my < this->renderRect.y + this->renderRect.h))
		{
			stop_input();
		} else if (!input_on) {
			start_input();
		}
	}
}

void TextInput::render(SDL_Renderer *ren)
{
	((View*)this)->render(ren);

	if (text.size() > 0)
	{
		string splice = text.substr(text_st_pos,text_count);

		SDL_Texture *text_tx = TextView::LoadText(splice.c_str(),font,ren,fgColor);
		SDL_RenderCopy(ren,text_tx,NULL,&textRect);
		SDL_DestroyTexture(text_tx);
	}

	int factor = cursor_pos - text_st_pos;
	cursor_rect.x = textRect.x + (factor*(textRect.w/(text_count==0?1:text_count)));

	int time = SDL_GetTicks();

	if (time - prev_time > 600)
	{
		if (cursor_opacity == 255)
			cursor_opacity = 0;
		else 
			cursor_opacity = 255;

		prev_time = time;
	}
	if (!input_on) cursor_opacity = 0;

	SDL_SetRenderDrawColor(ren, fgColor.r, fgColor.g, fgColor.b, cursor_opacity);
	SDL_RenderFillRect(ren,&cursor_rect);
}

} // namespace mango
