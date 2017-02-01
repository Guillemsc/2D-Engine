#include "j1Console.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "p2Point.h"
#include "j1FileSystem.h"
#include "j1Window.h"
#include "Functions.h"
#include <iostream>

using namespace std;

#define CONSOLE_HEIGHT 300
#define TOP_FRAME_SIZE 30
#define FRAMES_SIZE 15
#define SCROLL_BUTTON_SIZE 15
#define TEXT_DISTANCE 22

j1Console::j1Console()
{
	name.create("Console");
}

j1Console::~j1Console()
{
}

bool j1Console::Awake(pugi::xml_node &node)
{
	return true;
}

bool j1Console::Start()
{
	console_color = { 32, 32, 32, 200 };

	window = (UI_Window*)App->gui->UI_CreateWin(iPoint(App->render->camera.x, App->render->camera.y), 
			 App->render->camera.x + App->render->camera.w, CONSOLE_HEIGHT, false);
	window->always_top = true;

	colored_rect1 = (UI_ColoredRect*)window->CreateColoredRect(iPoint(window->rect.x, window->rect.y), window->rect.w, window->rect.h, console_color);
	colored_rect_top = (UI_ColoredRect*)window->CreateColoredRect(iPoint(window->rect.x, window->rect.y), window->rect.w, TOP_FRAME_SIZE, { 32, 32, 32, 255 });
	colored_rect_left = (UI_ColoredRect*)window->CreateColoredRect(iPoint(window->rect.x, window->rect.y), FRAMES_SIZE, CONSOLE_HEIGHT, { 32, 32, 32, 255 });
	colored_rect_right = (UI_ColoredRect*)window->CreateColoredRect(iPoint(window->rect.x + window->rect.w - FRAMES_SIZE, window->rect.y), FRAMES_SIZE, CONSOLE_HEIGHT, { 32, 32, 32, 255 });
	colored_rect_bottom = (UI_ColoredRect*)window->CreateColoredRect(iPoint(window->rect.x, CONSOLE_HEIGHT - FRAMES_SIZE), window->rect.w, FRAMES_SIZE, { 32, 32, 32, 255 });

	top_text = (UI_Text*)window->CreateText(iPoint(10, 4), App->font->default_15);
	top_text->SetText("Console");

	scroll = (UI_Scroll_Bar*)window->CreateScrollBar(iPoint(window->rect.x + FRAMES_SIZE, window->rect.y + TOP_FRAME_SIZE), window->rect.x + window->rect.w - (FRAMES_SIZE*2) - 15, CONSOLE_HEIGHT - FRAMES_SIZE - TOP_FRAME_SIZE, SCROLL_BUTTON_SIZE);

	bottom_scroll_v = (UI_ColoredRect*)window->CreateColoredRect(iPoint(scroll->button_v->rect.x, scroll->min_bar_v), scroll->button_v->rect.w, scroll->rect.h, {80, 80, 80, 200});
	bottom_scroll_v->click_through = true;
	top_scroll_v = (UI_ColoredRect*)window->CreateColoredRect(iPoint(scroll->button_v->rect.x, scroll->button_v->rect.y), scroll->button_v->rect.w, scroll->button_v->rect.h, { 40, 40, 40, 250 });
	top_scroll_v->click_through = true;

	bottom_scroll_h = (UI_ColoredRect*)window->CreateColoredRect(iPoint(scroll->min_bar_h, scroll->button_h->rect.y), scroll->rect.w, scroll->button_h->rect.h, { 80, 80, 80, 200 });
	bottom_scroll_h->click_through = true;
	top_scroll_h = (UI_ColoredRect*)window->CreateColoredRect(iPoint(scroll->button_h->rect.x, scroll->button_h->rect.y), scroll->button_h->rect.w, scroll->button_h->rect.h, { 40, 40, 40, 250 });
	top_scroll_h->click_through = true;

	colored_rect_text_input = (UI_ColoredRect*)window->CreateColoredRect(iPoint(window->rect.x, scroll->rect.y + scroll->rect.h + FRAMES_SIZE), window->rect.w, 25, { 32, 32, 32, 255 });
	text_input = (UI_Text_Input*)window->CreateTextInput(iPoint(window->rect.x + FRAMES_SIZE, scroll->rect.y + scroll->rect.h + FRAMES_SIZE), window->rect.w - FRAMES_SIZE, App->font->default_15);

	Log("Welcome to the console :-D");

	window->SetEnabledAndChilds(false);
	return true;
}

bool j1Console::PreUpdate()
{
	return true;
}

bool j1Console::Update(float dt)
{
	LoadLogs();

	if (App->input->GetKey(SDL_SCANCODE_GRAVE) == KEY_DOWN)
	{
		window->SetEnabledAndChilds(!window->enabled);
	}

	if (scroll->max_bar_v == scroll->moving_rect.h || !scroll->parent->enabled)
		top_scroll_v->enabled = false;
	else
		top_scroll_v->enabled = true;

	if (scroll->max_bar_h == scroll->moving_rect.w || !scroll->parent->enabled)
		top_scroll_h->enabled = false;
	else
		top_scroll_h->enabled = true;

	top_scroll_v->rect = { scroll->button_v->rect.x, scroll->button_v->rect.y, scroll->button_v->rect.w, scroll->button_v->rect.h };
	top_scroll_h->rect = { scroll->button_h->rect.x, scroll->button_h->rect.y, scroll->button_h->rect.w, scroll->button_h->rect.h };

	if (text_input->active && text_input->intern_text.Length() > 0)
	{
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			Tokenize(text_input->intern_text);
		}
	}

	if (scroll->button_v->MouseClickEnterLeft())
		stay_bottom = false;

	if (stay_bottom)
		scroll->button_v->rect.y = scroll->max_bar_v - scroll->button_v->rect.h;


	return true;
}

bool j1Console::Load(pugi::xml_node &node)
{
	return false;
}

bool j1Console::Save(pugi::xml_node &node) const
{

	return true;
}

bool j1Console::CleanUp()
{
	return true;
}

void j1Console::Log(p2SString string, uint r, uint g, uint b)
{
	if (string.Length() > 0)
	{
		UI_Text* text = new UI_Text();
		text->Set(iPoint(3, last_text_pos), App->font->default_15, 15, r, g, b);
		text->SetText(string.GetString());
		scroll->AddElement(text);
		last_text_pos += TEXT_DISTANCE;
		stay_bottom = true;
	}
}

void j1Console::Tokenize(p2SString s)
{
	p2List<p2SString> strings;
	p2List<float> ints;

	// Separate text and numbers ----------------

	SeparateTextAndNumbers(s, strings, ints);

	// ----------------------------------------

	Commands(s, strings, ints);

	text_input->Clear();

}

void j1Console::SeparateTextAndNumbers(p2SString s, p2List<p2SString>& strings, p2List<float>& ints)
{
	string cs = s.GetString();

	p2SString current;
	p2SString number;

	// Separate text and numbers ----------------

	for (int i = 0; i < s.Length(); i++)
	{
		if (cs[i] != ' ')
		{
			if (isdigit(cs[i]) || (isdigit(cs[i + 1]) && cs[i] == '-') || (isdigit(cs[i + 1]) && cs[i] == '.'))
			{
				if (current.Length() > 0)
				{
					strings.add(current);
					current.Clear();
				}

				if (number.Length() > 0)
					number.create("%s%c", number.GetString(), cs[i]);
				else
					number.create("%c", cs[i]);
			}
			else
			{
				if (!isdigit(cs[i]))
				{
					if (number.Length() > 0)
					{
						ints.add(atoi(number.GetString()));
						number.Clear();
					}
				}

				if (current.Length() > 0)
					current.create("%s%c", current.GetString(), cs[i]);
				else
					current.create("%c", cs[i]);
			}
		}
		else
		{
			if (current.Length() > 0)
			{
				strings.add(current);
				current.Clear();
			}

			if (number.Length() > 0)
			{
				ints.add(atoi(number.GetString()));
				number.Clear();
			}
		}
	}

	if (current.Length() > 0)
	{
		strings.add(current);
		current.Clear();
	}

	if (number.Length() > 0)
	{
		ints.add(atoi(number.GetString()));
		number.Clear();
	}

	// ----------------------------------------
}

void j1Console::Commands(p2SString s, p2List<p2SString>& strings, p2List<float>& ints)
{
	if (TextCmp(strings[0].GetString(), "help"))
	{
		Log(" ");
		Log("\nBasic commands:");
		Log("   - 'help': sends help :v.");
		Log("   - 'clear': clears the console text.");
		Log("   - 'hide': hides console.");
		Log("   - 'exit': exits program.");
		Log("   - 'debug (1 or 0)': sets debug mode.");
		Log("   - 'set title (string)': changes the window title.");
		Log("   - 'fps (float)': limits fps.");
		Log(" ");
	}
	else if (TextCmp(strings[0].GetString(), "clear"))
	{
		ClearConsole();
	}
	else if (TextCmp(strings[0].GetString(), "hide"))
	{
		window->SetEnabledAndChilds(!window->enabled);
	}
	else if (TextCmp(strings[0].GetString(), "debug"))
	{
		if (ints[0] == 1)
		{
			App->debug_mode = true;
			Log("> Debug mode ON", succes.r, succes.g, succes.b);
		}
		if (ints[0] == 0)
		{
			App->debug_mode = false;
			Log("> Debug mode OFF", succes.r, succes.g, succes.b);
		}
	}
	else if (TextCmp(strings[0].GetString(), "exit"))
	{
		Log("Exiting program");
		App->EndSDL();
	}
	else if (TextCmp(strings[0].GetString(), "set") && strcmp(strings[1].GetString(), "title") == 0)
	{
		Log(p2SString("Title changed to '%s'.", strings[2].GetString()), succes.r, succes.g, succes.b);
		App->win->SetTitle(strings[2].GetString());
	}
	else if (TextCmp(strings[0].GetString(), "fps"))
	{
		if (ints.count() > 0)
		{
			App->CapFps(ints[0]);
			Log(p2SString("> Fps limited to %0f.", ints[0]), succes.r, succes.g, succes.b);
		}

	}
	else if (TextCmp(strings[0].GetString(), "hi"))
	{
		Log("Hi! :D");
	}
	else
	{
		Log(p2SString("> The command '%s' does not exist. Type 'help' for some info.", s.GetString()), error.r, error.g, error.b);
	}
}

void j1Console::ClearConsole()
{
	last_text_pos = 1;
	scroll->ClearElements();
}

void j1Console::LoadLogs()
{
	for (int i = 0; i < App->logs.count(); i++)
	{
		Log(App->logs[i].GetString());
	}

	App->logs.clear();	
}

