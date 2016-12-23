#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "j1Fonts.h"
#include "p2PQueue.h"

#define CURSOR_WIDTH 2

enum ui_element
{
	ui_text_input,
	ui_button,
	ui_text,
	ui_image,
	ui_window,
	ui_scroll_bar,
	ui_colored_rect
};

// -----------------------------------------
// -----------------------------------------

		        // UI :D //

// -----------------------------------------
// -----------------------------------------

// Class Gui -------------------------
// -----------------------------------

struct TTF_Font;
class UI_Element;
class UI_Window;
class UI_Text;
class UI_WindowManager;

class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	bool Update(float dt);

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Gets the atlas texture
	const void GetAtlas() const;

	UI_Element* UI_CreateWin(iPoint pos, int w, int h, bool dinamic = false);

	void UI_CreateWinManager(iPoint pos, int w, int h, bool dinamic = false);

	void Tab();

	void GetChilds(UI_Element * element, p2List<UI_Element*>& visited);
	void GetAlwaysTopElements(p2List<UI_Element*>& always_top);
	void ReorderElements();

private:

public:
	// Atlas --
	SDL_Texture*		   atlas = nullptr;
	p2SString			   atlas_file_name;
	// --------

	// All elements
	p2PQueue<UI_Element*>  elements_list;
	uint				   higher_layer = 0;

	// Elements that can tab
	p2List<UI_Element*>    tab_list;

	// All windows
	p2List<UI_Window*>     windows;

	// Window Manager
	UI_WindowManager*	   window_manager = nullptr;

	// Debug when F1
	bool				   debug = false;

private:
	bool				   start = true;
};

// -------------------------
// ------------------------- Class Gui

// -----------------------------------
// Element ---------------------------

class UI_Element
{
public:
	UI_Element();
	~UI_Element();

	virtual bool update();

	// Enable function
	void SetEnabled(bool set);
	void SetEnabledAndChilds(bool set);

	// Child functions
	void AddChild(UI_Element* child);
	void AddChildBoth(UI_Element* child);

	// Mouse functions
	bool MouseClickEnterLeftIntern();
	bool MouseClickOutLeftIntern();

	void SetDebugColor(SDL_Color color);

protected:

	// Helper functions
	bool PutWindowToTop();
	int  CheckClickOverlap(int x, int y);

	// Window general movement
	bool Move_Element();

public:
	ui_element          type;
	SDL_Rect            rect;

	bool                print = true;
	bool				dinamic = false;
	bool				enabled = true;
	bool				click_through = false;
	bool				always_top = false;

	// Layers --
	int				    layer = 0;
	p2List<UI_Element*> childs;
	UI_Window*			parent = nullptr;
	// ----------

	//bool		        highlighted;

protected:
	SDL_Color			color;

private:
	// Moving ---
	bool			    moving = false;
	int					mouse_x;
	int					mouse_y;
	bool				clicked = false;
	// ----------
};


// ---------------------------
// --------------------------- Element

// -----------------------------------
// Window ----------------------------

class UI_Window : public UI_Element
{
public:
	UI_Window();
	~UI_Window();

	bool update();

	void Set(iPoint pos, int w, int h);

	UI_Element* CreateButton(iPoint _pos, int w, int h, bool dinamic = false);
	UI_Element* CreateText(iPoint pos, _TTF_Font* font, int spacing = 0, bool dinamic = false, uint r = 255, uint g = 255, uint b = 255);
	UI_Element* CreateImage(iPoint pos, SDL_Rect image, bool dinamic = false);
	UI_Element* CreateTextInput(iPoint pos, int w, _TTF_Font* font, bool dinamic = false, uint r = 255, uint g = 255, uint b = 255);
	UI_Element* CreateScrollBar(iPoint pos, int view_w, int view_h, int scroll, int button_size = 11, bool dinamic = false);
	UI_Element* CreateColoredRect(iPoint pos, int view_w, int view_h, SDL_Color color, bool filled = true, bool dinamic = false);

public:

};

// ----------------------------
// ---------------------------- Window

// -----------------------------------
// Button ----------------------------

class UI_Button : public UI_Element
{
public:
	UI_Button();

	~UI_Button();

	void Set(iPoint _pos, int w, int h);

	bool update();

	bool MouseEnter();
	bool MouseOut();
	bool MouseClickEnterLeft();
	bool MouseClickOutLeft();
	bool MouseClickEnterRight();
	bool MouseClickOutRight();

	void AddImage(SDL_Rect rect);
	void SetImage(int index);

public:

private:
	p2List<SDL_Rect>  rect_list;
	SDL_Rect		  curr;

	bool			  enter = false;

	bool			  clicked_left = false;
	bool			  clicked_right = false;
};

// ----------------------------
// ---------------------------- Button

// -----------------------------------
// Text ------------------------------

class UI_Text : public UI_Element
{
public:
	UI_Text();
	~UI_Text();

	bool update();

	void Set(iPoint pos, _TTF_Font* font, int spacing,  uint r, uint g, uint b);
	void SetText(p2SString text);

public:
	p2List<p2SString>   texts;
	SDL_Color	        color;
	_TTF_Font*	        font = nullptr;
	int                 spacing = 0;
};

// ------------------------------
// ------------------------------ Text

// -----------------------------------
// Image -----------------------------

class UI_Image : public UI_Element
{
public:
	UI_Image();
	~UI_Image();

	bool update();

	void Set(iPoint pos, SDL_Rect image);

	void ChangeImage(SDL_Rect rect);

public:
	SDL_Rect image;
};

// -----------------------------
// ----------------------------- Image

// -----------------------------------
// Text Input ------------------------

class UI_Text_Input : public UI_Element
{
public:
	UI_Text_Input();
	~UI_Text_Input();

	bool update();

	void Set(iPoint pos, int w, _TTF_Font* font, uint r, uint g, uint b);


	char* Enter();

private:
	void SetIsActive();

	bool MouseClick();

	bool TakeInput();
	bool Delete();
	void MoveCursor();
	void UpdateWordsLenght(p2SString l_text);
	void DrawBar();
	void SetPasword();

public:
	p2SString	 intern_text;
	bool		 pasword = false;
	UI_Text*	 text = nullptr;

private:
	SDL_Rect	 bar;
	uint		 bar_pos = 0;
	uint		 bar_x = 0;

	bool		 active = false;
	p2List<int>	 words_lenght;
};

// -----------------------------
// ------------------------ Text Input

// -----------------------------------
// Scroll Bar ------------------------

class UI_Scroll_Bar : public UI_Element
{
public:
	UI_Scroll_Bar();
	~UI_Scroll_Bar();

	void Set(iPoint pos, int w, int h, int scroll, int button_size = 11);

	bool update();

	UI_Element* AddButton(iPoint _pos, int w, int h, bool dinamic = false);
	UI_Element* AddText(iPoint pos, _TTF_Font* font, int spacing, uint r, uint g, uint b, bool dinamic = false);
	UI_Element* AddImage(iPoint pos, SDL_Rect image, bool dinamic = false);
	UI_Element* AddTextInput(iPoint pos, int w, _TTF_Font* font, uint r, uint g, uint b, bool dinamic = false);

private:
	bool ScrollWindow();
	void AddElement(UI_Element* element);
	void SetMinMaxBar();
	float GetSpeed(int size);

public:
	UI_Button* button = nullptr;

private:
	p2List<UI_Element*> elements;
	SDL_Rect viewport_rect;

	// Movement
	int mouse_y;
	bool is_scrolling = false;
	int bar_pos = 0;
	int scroll = 0;

	// Bar
	int max_bar = 0;
	int min_bar = 0;
	int bar_distance = 0;

};

// ------------------------
// ------------------------ Scroll Bar

struct WindowManagerObject
{
	WindowManagerObject() {};
	WindowManagerObject(SDL_Rect _rect, UI_Window* _window)
	{
		button = new UI_Button();
		button->Set(iPoint(_rect.x, _rect.y), _rect.w, _rect.h);
		window = _window;
	};

	~WindowManagerObject() {};

	UI_Button* button = nullptr;
	UI_Window* window = nullptr;
};

class UI_WindowManager : public UI_Element
{
public:
	UI_WindowManager();
	~UI_WindowManager();

	void Set(iPoint pos, int w, int h);

	bool update();

private:
	void SetObjects();
	void UpdateWindowObjects();
	void MinimizeOrMaximise();

	p2List<WindowManagerObject> windows_rects;

private:
	int max_w = 0;
	bool one_time = false;

};

class UI_ColoredRect : public UI_Element
{
public:
	UI_ColoredRect();
	~UI_ColoredRect();

	void Set(iPoint pos, int w, int h, SDL_Color color, bool filled = true);

	bool update();

	void SetColor(SDL_Color color);

public:
	
private:
	SDL_Color color;
	bool filled = true;
};

#endif // __j1GUI_H__