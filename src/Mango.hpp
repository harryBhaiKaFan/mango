#ifndef __MANGO_EDITOR_HPP__
#define __MANGO_EDITOR_HPP__

#include <cstdio>
#include <iostream>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "ui/TextView.hpp"
#include "ui/View.hpp"
#include "ui/Button.hpp"
#include <vector>

#define FONT_PATH "./font/FiraMonoNerdFontMono-Medium.otf"

using namespace std;

namespace mango
{

	class Header: public View
	{
		private:
			static Header *header;

			Button newFile;
			Button saveFile;
			Button openFile;
			Button closeFile;

			Header(SDL_Renderer *ren);
		public:
			static Header* get(SDL_Renderer *ren);
			void process_events(SDL_Event *e);
			void render(SDL_Renderer *ren);
	};

	class TabNav: public View
	{
		private:
			static TabNav *tabnav;
			size_t current_active_tab = 0;
			vector<Button> tabs;
			vector<string> tab_texts;

			TabNav(SDL_Renderer *ren);
		public:
			static TabNav* get(SDL_Renderer *ren);
			void process_events(SDL_Event *e);
			void render(SDL_Renderer *ren);
			friend void* new_file_fn(void*);
			friend void* open_file_fn(void*);
	};

	class Editor: public View
	{
		private:
			static Editor *editor;
			SDL_Color fgColor;
			SDL_Rect cursor;
			vector<TextView> line_nos;
			vector<SDL_Rect> text_rects;
			TTF_Font *font = NULL;

			Editor(SDL_Renderer *ren);
		public:

			string text = "Hello,World";
			bool keydown = false;

			int cursorA = 255;
			uint32_t lp = 0;
			uint32_t cp = 0;
			
			bool editing = false;

			static Editor* get(SDL_Renderer *ren);
			void start_edit();
			void stop_edit();
			void add_line();
			void remove_line();
			void get_text();
			void set_text();
			void process_events(SDL_Event *e);
			void render(SDL_Renderer*);
	};


} // namespace mango


#endif
