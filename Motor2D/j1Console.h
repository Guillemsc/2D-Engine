#ifndef __j1CONSOLE_H__
#define __j1CONSOLE_H__

#include "j1Module.h"
#include "p2Point.h"
#include "p2List.h"
#include "j1Fonts.h"

class UI_Window;
class UI_Text;
class UI_ColoredRect;
class UI_Scroll_Bar;
class UI_Text_Input;
class j1Console : public j1Module
{
public:
	j1Console();

	// Destructor
	virtual ~j1Console();

	// Called before render is available
	bool Awake(pugi::xml_node& node);

	bool Start();

	bool PreUpdate();
	bool Update(float dt);
	
	bool Load(pugi::xml_node& node);
	bool Save(pugi::xml_node& node) const;

	// Called before quitting
	bool CleanUp();

	void Log(p2SString string, uint r = 245, uint g = 245, uint b = 245);
	void Tokenize(p2SString string);
	void SeparateTextAndNumbers(p2SString text, p2List<p2SString> &strings, p2List<float> &ints);
	void Commands(p2SString text, p2List<p2SString> &strings, p2List<float> &ints);
	void ClearConsole();

	void LoadLogs();

private:
	int last_text_pos = 1;

public:
	SDL_Color console_color;
	UI_Scroll_Bar* scroll = nullptr;

private:
	UI_Window* window = nullptr;
	p2List<UI_Text*> console_text;

	UI_ColoredRect* colored_rect1 = nullptr;
	UI_ColoredRect* colored_rect_top = nullptr;
	UI_ColoredRect* colored_rect_left = nullptr;
	UI_ColoredRect* colored_rect_right = nullptr;
	UI_ColoredRect* colored_rect_bottom = nullptr;
	UI_ColoredRect*	colored_rect_text_input = nullptr;
	UI_ColoredRect*	colored_rect_text_input2 = nullptr;
	UI_Text* top_text = nullptr;

	UI_ColoredRect* bottom_scroll_v = nullptr;
	UI_ColoredRect* top_scroll_v = nullptr;

	UI_ColoredRect* bottom_scroll_h = nullptr;
	UI_ColoredRect* top_scroll_h = nullptr;

	UI_Text_Input* text_input = nullptr;

	bool stay_bottom = true;

	SDL_Color error = { 255, 67, 67, 255 };
	SDL_Color succes = { 0, 178, 255, 255 };

};

#endif // __j1CONSOLE_H__