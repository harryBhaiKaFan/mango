#ifndef __MANGO_EDITOR_HPP__
#define __MANGO_EDITOR_HPP__

#include <cstdio>
#include <iostream>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

namespace mango
{

	class Editor
	{
		private:
			static Editor *editor;
			SDL_Color fg = {
				.r = 225,
				.g = 245,
				.b = 225,
				.a = 255
			};
			SDL_Rect rect = {
				.x=0,.y=0,.h=60
			};

			SDL_Rect cursor = {
				.x=0,.y=0,.w=10,.h=60
			};
			Editor() {}
		public:

			string text = "";
			bool keydown = false;

			int cursorA = 255;
			uint32_t lp = 0;
			uint32_t cp = 0;
			static Editor* get()
			{
				if (editor == NULL)
					editor = new Editor();

				return editor;
			}

			void render(SDL_Renderer *ren)
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
			~Editor() {}

	};


}


#endif
