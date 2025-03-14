#ifndef __MANGO_EDITOR_HPP__
#define __MANGO_EDITOR_HPP__

#include <cstdio>
#include <iostream>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "ui/View.hpp"
#include "ui/Button.hpp"

using namespace std;

namespace mango
{

	class Header: public View
	{
		private:
			static Header *header;
			SDL_Color bg;
			SDL_Rect rect;

			Button newFile;
			Button saveFile;
			Button openFile;
			Button closeFile;
		public:

			void process_events(SDL_Event *e);
			void render(SDL_Renderer *ren);
	};

	class TabNav: public View
	{
		private:
			static TabNav *tabnav;
			SDL_Color bg;
			SDL_Rect rect;

			Button *openedFiles;

		public:

			void process_events(SDL_Event *e);
			void render(SDL_Renderer *ren);
	};

	class Editor: public View
	{
		private:
			static Editor *editor;
			SDL_Color fg;
			SDL_Color bg;
			SDL_Rect rect;
			SDL_Rect cursor;
			Editor();
		public:

			string text = "";
			bool keydown = false;

			int cursorA = 255;
			uint32_t lp = 0;
			uint32_t cp = 0;
			
			static Editor* get();
			
			void process_events(SDL_Event *e);
			void render(SDL_Renderer*);
	};


} // namespace mango


#endif
