#include "TextView.hpp"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <cstring>
#include <iostream>

using namespace std;

namespace mango
{

TextView::TextView(const char *text,const char *font_path,SDL_Renderer *ren,SDL_Color bgColor,SDL_Color fgColor,SDL_Rect rect,Text_Alignment talgn = TEXT_ALIGN_LEFT):View(bgColor,rect)
{
	this->textRect = rect;
	TTF_Font *font = TTF_OpenFont(font_path, (0.75)*textRect.h);

	int tw = 0, count = 0;
	TTF_MeasureText(font,text,textRect.w,&tw,&count);

	if (count < strlen(text)) cerr << "Text overflow!" << endl;
	if (count == 0) cerr << "View width too small, 0 char rendered!" << endl;

	if (textRect.w > tw)
	{
		textRect.w = tw;
	}
	string s = text;
	text = s.substr(0,count).c_str();

	if (talgn == TEXT_ALIGN_RIGHT)
	{
		textRect.x = rect.x + rect.w - textRect.w;
	} else if (talgn == TEXT_ALIGN_CENTER)
	{
		textRect.x = rect.x + rect.w/2 - textRect.w/2;
	}

	this->text_tx = LoadText(text,font,ren,fgColor);
}

void TextView::set_y(uint32_t y)
{
	this->rect.y = y;
	this->textRect.y = y;
}

SDL_Texture* TextView::LoadText(const char *text,TTF_Font *font,SDL_Renderer* ren,SDL_Color color)
{
	SDL_Surface *sf = TTF_RenderText_Blended(font, text,color);
	if (sf == NULL) cerr << "Failed to render text!" << endl;
	SDL_Texture *tx = SDL_CreateTextureFromSurface(ren,sf);
	if (tx == NULL) cerr << "Failed to create texture!" << endl;

	SDL_FreeSurface(sf);
	return tx;
}

void TextView::render(SDL_Renderer *ren)
{
	((View*)this)->render(ren);
	SDL_RenderCopy(ren,this->text_tx,NULL,&this->textRect);
}

}
