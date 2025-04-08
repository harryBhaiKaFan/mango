#ifndef __MANGO_EDITOR_HPP__
#define __MANGO_EDITOR_HPP__

#include <cstdio>
#include <iostream>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "ui/TextView.hpp"
#include "ui/TextInput.hpp"
#include "ui/View.hpp"
#include "ui/Button.hpp"
#include <vector>

#define FONT_PATH "./font/FiraMonoNerdFontMono-Medium.otf"

using namespace std;

namespace mango
{

	void* new_file_fn(void*);
	void* open_file_fn(void*);
	void* save_file_fn(void*);
	void* close_file_fn(void*);
	void* select_tab(void*);

	class PopInput: public View
	{
		private:
			TextInput inp;
			Button ok;
		public:

			PopInput(SDL_Renderer *ren,SDL_Color bgColor);
			void process_events(SDL_Event *e);
			void render(SDL_Renderer *ren);
	};

	class Header: public View
	{
		private:
			static Header *header;

			Button newFile;
			Button saveFile;
			Button openFile;
			Button closeFile;

			PopInput popInput;

			Header(SDL_Renderer *ren);
		public:
			bool popInput_active = false;
			static Header* get(SDL_Renderer *ren);
			void process_events(SDL_Event *e);
			void render(SDL_Renderer *ren);
	};



	class Tab: public View
	{
		private:
			Button btn;
			string file_path = "";

		public:
			Tab(Button b, void* (*fn)(void*));
			void setSavedState(bool saved);
			void process_events(SDL_Event *e);
			void render(SDL_Renderer *ren);
	};
	class TabNav: public View
	{
		private:
			static TabNav *tabnav;
			size_t current_active_tab = 0;
			vector<Tab> tabs;

			TabNav(SDL_Renderer *ren);
		public:
			static TabNav* get(SDL_Renderer *ren);
			void process_events(SDL_Event *e);
			void render(SDL_Renderer *ren);
			friend void* new_file_fn(void*);
			friend void* open_file_fn(void*);
			friend void* save_file_fn(void*);
			friend void* close_file_fn(void*);
			friend void* select_tab(void*);
	};

	class Editor: public View
	{
		private:
			static Editor *editor;
			SDL_Color fgColor;
			SDL_Rect cursor;
			size_t current_active_line = 0;
			vector<TextView> line_nos;
			vector<SDL_Rect> text_rects;
			vector<string> str_chunks;
			TTF_Font *font = NULL;
			string text = "Hello,World";
			uint32_t text_size = 24;

			Editor(SDL_Renderer *ren);
		public:

			bool keydown = false;

			int cursorA = 255;
			uint32_t lp = 0;
			uint32_t cp = 0;

			bool editing = false;

			static Editor* get(SDL_Renderer *ren);
			void start_edit();
			void stop_edit();
			void add_line(int line_before);
			void remove_line(int line_no);
			string get_text();
			void set_text(string s);
			void process_events(SDL_Event *e);
			void render(SDL_Renderer*);
	};


} // namespace mango


#endif
