#include "Mango.hpp"
#include "render/Render.hpp"
#include "render/Window.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
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
	
	Button btn{
		"Unnamed",
		ren,
		{tab_btn_gap + (int)tabnav->tabs.size()*100,tabnav_rect.y,100,20},
		FONT_PATH,
		button_bg,
		button_fg,
		0
	};

	Tab tab = {btn,select_tab};
	tabnav->tabs.push_back(tab);

	return NULL;
}

void* save_file_fn(void*)
{
	TabNav *tabnav = TabNav::get(NULL);

	//tabnav
	return NULL;
}

void* open_file_fn(void *data)
{
	extern int tab_btn_gap;
	extern SDL_Rect tabnav_rect;
	SDL_Renderer *ren = (SDL_Renderer*)data;
	TabNav *tabnav = TabNav::get(NULL);
	Header *header = Header::get(NULL);

	header->popInput_active = true;

	
	return NULL;
}

void* close_file_fn(void*)
{
	TabNav *tabnav = TabNav::get(NULL);

	return NULL;
}

// tab button functions

void* select_tab(void* data)
{
	Tab *curr_tab = (Tab*) data;
	TabNav *tb = TabNav::get(NULL);

	return NULL;
}

// PopInput starts here

SDL_Rect popup_rect = {
	(WINDOW_WIDTH/2) - (250/2),
	(WINDOW_HEIGHT/2) - (100/2),
	250,
	100
};
SDL_Rect popup_inp_rect = {
	popup_rect.x+popup_rect.w/2-(200/2),
	popup_rect.y+20,
	200,
	25
};
SDL_Rect popup_btn_rect = {
	popup_rect.x+popup_rect.w/2-(30/2),
	popup_inp_rect.y + popup_inp_rect.h + 25,
	30,
	15
};

void* popup_btn_click(void* data)
{
	Header *header = Header::get(NULL);
	header->popInput_active = false;

	return NULL;
}

PopInput::PopInput(SDL_Renderer *ren,SDL_Color bgColor = {50,50,50,255}):
	View(bgColor,popup_rect),
	inp(FONT_PATH,popup_inp_rect,{255,255,255,255},{0,0,0,255},10),
	ok("OK",ren, popup_btn_rect,FONT_PATH,{30,30,30,255}, {255,255,255,255}, 10)
{
	this->ok.attach_click_listener(popup_btn_click);
}

void PopInput::process_events(SDL_Event *e)
{
	inp.process_events(e);
	ok.process_events(e);
}

void PopInput::render(SDL_Renderer *ren)
{
	((View*)this)->render(ren);
	this->inp.render(ren);
	this->ok.render(ren);
}


// PopInput ends here

// Header starts here
SDL_Color header_bg = {45,45,45,255};
int header_padding = 20;
SDL_Rect header_rect = { header_padding,header_padding,WINDOW_WIDTH,20 };

Header* Header::header = NULL;


Header::Header(SDL_Renderer *ren):
	View(header_bg,header_rect),
	popInput(ren),
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

	if (popInput_active)
		popInput.process_events(e);
}

void Header::render(SDL_Renderer *ren)
{
	((View*)this)->render(ren);
	newFile.render(ren);
	saveFile.render(ren);
	openFile.render(ren);
	closeFile.render(ren);

	if (popInput_active)
		popInput.render(ren);
}

Header* Header::get(SDL_Renderer *ren)
{
	if (header == NULL && ren != NULL)
		header = new Header(ren);

	return header;
}
// Header ends here

// Tab starts here


Tab::Tab(Button b,void* (*fn)(void*)):
	View({0},{0}),
	btn(b)
{
	this->btn.attach_click_listener(fn);
	this->btn.click_param_data = this;

	this->setSavedState(false);
}

void Tab::setSavedState(bool saved)
{
	if (!saved) 
	{
		btn.set_border({255,255,0,255});
		return;
	}

	btn.set_border({0});
}

void Tab::process_events(SDL_Event *e)
{
	this->btn.process_events(e);
}

void Tab::render(SDL_Renderer *ren)
{
	this->btn.render(ren);
}

// Tab ends here

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
	Button untitled_tab{
		"Unnamed",
			ren,
			{tab_btn_gap,tabnav_rect.y,100,20},
			FONT_PATH,
			button_bg,
			button_fg,
			0
	};
	this->tabs.push_back(Tab{untitled_tab,select_tab});
}

void TabNav::process_events(SDL_Event *e)
{
	for (Tab tab: tabs)
		tab.process_events(e);
}

void TabNav::render(SDL_Renderer *ren)
{
	((View*)this)->render(ren);

	for (Tab tab: tabs)
	{
		tab.render(ren);
	}
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
	this->start_edit();
	this->add_line(0);
}

void Editor::start_edit()
{
	SDL_StartTextInput();
}

void Editor::stop_edit()
{
	SDL_StopTextInput();
}

void Editor::add_line(int line_before) // 0-indexed line before
{
	SDL_Rect textRect = {.x=0,.y=editor_rect.y+editor_rect.h,.w=WINDOW_WIDTH};

	this->font = LoadFont(FONT_PATH, text_size);
	int extent, count;

	TTF_MeasureText(font, text.c_str(), textRect.w, &extent, &count);

	if (textRect.w > extent) textRect.w = extent;
	textRect.h = text_size * 1.3;
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

	text_rects.insert(text_rects.begin()+line_before,textRect);
}

void Editor::remove_line(int line_no) // 0-indexed line no.
{
	line_nos.erase(line_nos.begin() + line_no);
	text_rects.erase(text_rects.begin() + line_no);
	str_chunks.erase(str_chunks.begin() + line_no);
}

string Editor::get_text()
{
	return this->text;
}

void Editor::set_text(string s)
{
	this->text = s;
}


void Editor::process_events(SDL_Event *e)
{
}

void Editor::render(SDL_Renderer *ren)
{
	((View*)this)->render(ren);

	for (size_t i = 0; i < line_nos.size(); i++)
	{

	}
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
