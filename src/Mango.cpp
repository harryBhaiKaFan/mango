#include "Mango.hpp"
#include "render/Render.hpp"
#include "render/Window.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <cstddef>
#include <stdio.h>


namespace mango
{

// Global config
SDL_Color button_bg = {70,70,70,255};
SDL_Color button_fg = {255,255,255,255};

const char *curr_op_fp = NULL;

// Header button functions

void* new_file_fn(void* data)
{
	extern int tab_btn_gap;
	extern SDL_Rect tabnav_rect;
	SDL_Renderer *ren = (SDL_Renderer*)data;
	TabNav *tabnav = TabNav::get(NULL);

	cout << tabnav->tabs.size() << endl; 
	
	Button untitled_tab{
		"Unnamed",
		ren,
		{tab_btn_gap + (int)tabnav->tabs.size()*100,tabnav_rect.y,100,20},
		FONT_PATH,
		button_bg,
		button_fg,
		0
	};

	tabnav->tabs.push_back(untitled_tab);

	return NULL;
}

void* save_file_fn(void*)
{

	return NULL;
}

void* open_file_fn(void *data)
{
	extern int tab_btn_gap;
	extern SDL_Rect tabnav_rect;
	SDL_Renderer *ren = (SDL_Renderer*)data;
	TabNav *tabnav = TabNav::get(NULL);

	Button untitled_tab{
		"Unnamed",
		ren,
		{tab_btn_gap + (int)tabnav->tabs.size()*100,tabnav_rect.y,100,20},
		FONT_PATH,
		button_bg,
		button_fg,
		0
	};

	return NULL;
}

void* close_file_fn(void*)
{
	return NULL;
}

// tab button functions

void* select_tab(void*)
{
	return NULL;
}

// Header starts here
SDL_Color header_bg = {45,45,45,255};
int header_padding = 20;
SDL_Rect header_rect = { header_padding,header_padding,WINDOW_WIDTH,20 };

Header* Header::header = NULL;


Header::Header(SDL_Renderer *ren):
	View(header_bg,header_rect),
	newFile("New", ren,{header_padding+0, header_rect.y, 60, 20},FONT_PATH,button_bg,button_fg, 5),
	saveFile("Save", ren, {header_padding+90,header_rect.y,60,20},FONT_PATH,button_bg,button_fg,5),
	openFile("Open",ren,{header_padding+180,header_rect.y,60,20},FONT_PATH,button_bg,button_fg,5),
	closeFile("Close",ren,{header_padding+270,header_rect.y,60,20},FONT_PATH,button_bg,button_fg,5)
{
	this->padding_block(header_padding);
	this->padding_inline(header_padding);
	this->paddingR = 0;

	this->newFile.attach_click_listener(new_file_fn);
	this->newFile.click_param_data = ren;
	
	this->saveFile.attach_click_listener(save_file_fn);
	
	this->openFile.attach_click_listener(open_file_fn);
	this->openFile.click_param_data = ren;

	this->closeFile.attach_click_listener(close_file_fn);
}

void Header::process_events(SDL_Event *e)
{
	newFile.process_events(e);
	saveFile.process_events(e);
	openFile.process_events(e);
	closeFile.process_events(e);
}

void Header::render(SDL_Renderer *ren)
{
	((View*)this)->render(ren);
	newFile.render(ren);
	saveFile.render(ren);
	openFile.render(ren);
	closeFile.render(ren);
}

Header* Header::get(SDL_Renderer *ren)
{
	if (header == NULL && ren != NULL)
		header = new Header(ren);

	return header;
}
// Header ends here

// TabNav starts here

SDL_Color tabnav_bg = {60,60,60,255};

SDL_Rect tabnav_rect = {
	0,
	header_rect.y + header_rect.h + (header_padding),
	WINDOW_WIDTH,
	20
};

int tab_btn_gap = 20;

TabNav* TabNav::tabnav = NULL;

TabNav::TabNav(SDL_Renderer *ren):View(tabnav_bg,tabnav_rect)
{
	// this->setBorder({0,255,255,255});
	Button untitled_tab{
		"Unnamed",
		ren,
		{tab_btn_gap,tabnav_rect.y,100,20},
		FONT_PATH,
		button_bg,
		button_fg,
		0
	};

	this->tabs.push_back(untitled_tab);
}

void TabNav::process_events(SDL_Event *e)
{
	for (Button tab: tabs)
		tab.process_events(e);
}

void TabNav::render(SDL_Renderer *ren)
{
	((View*)this)->render(ren);

	for (Button tab: tabs)
		tab.render(ren);
}

TabNav* TabNav::get(SDL_Renderer *ren)
{
	if (TabNav::tabnav == NULL && ren != NULL)
		tabnav = new TabNav(ren);

	if (TabNav::tabnav == NULL) cerr << "Unconstructed TabNav!" << endl;
	return tabnav;
}

// TabNav ends here


// Editor starts here
SDL_Color editor_bg = {120,30,30,255};
SDL_Rect editor_rect = {
	20,
	tabnav_rect.y + tabnav_rect.h + 20,
	WINDOW_WIDTH,
	WINDOW_HEIGHT - (tabnav_rect.y + tabnav_rect.h)
};

Editor* Editor::editor = NULL;

Editor::Editor(SDL_Renderer *ren):View(editor_bg,editor_rect)
{
	this->padding(20);
	text_rects.push_back(rect);

	SDL_Rect &textRect = text_rects[0];

	this->font = LoadFont(FONT_PATH, 24);
	int extent, count;

	TTF_MeasureText(font, text.c_str(), textRect.w, &extent, &count);
	
	if (textRect.w > extent) textRect.w = extent;
	textRect.h = 24 * 1.3;
	text = text.substr(0,count);

	this->fgColor = (SDL_Color){
				.r = 225,
				.g = 245,
				.b = 225,
				.a = 255
	};

	this->cursor = (SDL_Rect){
		.x=0,.y=0,.w=10,.h=60
	};
}

void Editor::start_edit()
{

}

void Editor::stop_edit()
{

}

void Editor::add_line()
{

}

void Editor::remove_line()
{
}

void Editor::get_text()
{
}

void Editor::set_text()
{
}


void Editor::process_events(SDL_Event *e)
{
	if (e->type == SDL_MOUSEWHEEL_NORMAL)
	{
		return;
	}else if (e->type == SDL_MOUSEWHEEL_FLIPPED)
	{
		return;
	}
}

void Editor::render(SDL_Renderer *ren)
{
	((View*)this)->render(ren);

	SDL_Texture *text_tx = TextView::LoadText(text.c_str(),font,ren,fgColor);
	SDL_RenderCopy(ren,text_tx,NULL,&text_rects[0]);
}

Editor* Editor::get(SDL_Renderer *ren)
{
	if (editor == NULL && ren != NULL)
		editor = new Editor(ren);

	return editor;
}
// Editor ends here


} // namespace mango
