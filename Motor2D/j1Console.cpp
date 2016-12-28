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

#define CONSOLE_HEIGHT 300
#define TOP_FRAME_SIZE 30
#define FRAMES_SIZE 15
#define SCROLL_BUTTON_SIZE 15
#define TEXT_DISTANCE 22

j1Console::j1Console()
{
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
			 App->render->camera.x + App->render->camera.w, CONSOLE_HEIGHT, true);
	window->always_top = true;

	colored_rect1 = (UI_ColoredRect*)window->CreateColoredRect(iPoint(window->rect.x, window->rect.y), window->rect.w, window->rect.h, console_color);
	colored_rect_top = (UI_ColoredRect*)window->CreateColoredRect(iPoint(window->rect.x, window->rect.y), window->rect.w, TOP_FRAME_SIZE, { 32, 32, 32, 255 });
	colored_rect_left = (UI_ColoredRect*)window->CreateColoredRect(iPoint(window->rect.x, window->rect.y), FRAMES_SIZE, CONSOLE_HEIGHT, { 32, 32, 32, 255 });
	colored_rect_right = (UI_ColoredRect*)window->CreateColoredRect(iPoint(window->rect.x + window->rect.w - FRAMES_SIZE, window->rect.y), FRAMES_SIZE, CONSOLE_HEIGHT, { 32, 32, 32, 255 });
	colored_rect_bottom = (UI_ColoredRect*)window->CreateColoredRect(iPoint(window->rect.x, CONSOLE_HEIGHT - FRAMES_SIZE), window->rect.w, FRAMES_SIZE, { 32, 32, 32, 255 });

	top_text = (UI_Text*)window->CreateText(iPoint(10, 4), App->font->default_15);
	top_text->SetText("Console");

	scroll = (UI_Scroll_Bar*)window->CreateScrollBar(iPoint(window->rect.x + FRAMES_SIZE, window->rect.y + TOP_FRAME_SIZE), window->rect.x + window->rect.w - (FRAMES_SIZE*2) - 15, CONSOLE_HEIGHT - FRAMES_SIZE - TOP_FRAME_SIZE, SCROLL_BUTTON_SIZE);

	//bottom_scroll_v = (UI_ColoredRect*)window->CreateColoredRect(iPoint(scroll->button_v->rect.x, scroll->min_bar_v), scroll->button_v->rect.w, scroll->rect.h, {80, 80, 80, 200});
	//bottom_scroll_v->click_through = true;
	//top_scroll_v = (UI_ColoredRect*)window->CreateColoredRect(iPoint(scroll->button_v->rect.x, scroll->button_v->rect.y), scroll->button_v->rect.w, scroll->button_v->rect.h, { 40, 40, 40, 250 });
	//top_scroll_v->click_through = true;

	/*bottom_scroll_h = (UI_ColoredRect*)window->CreateColoredRect(iPoint(scroll->min_bar_h, scroll->button_h->rect.y), scroll->button_h->rect.w, scroll->button_h->rect.h, { 80, 80, 80, 200 });
	bottom_scroll_h->click_through = true;
	top_scroll_h = (UI_ColoredRect*)window->CreateColoredRect(iPoint(scroll->button_h->rect.x, scroll->button_h->rect.y), scroll->button_h->rect.w, scroll->button_h->rect.h, { 40, 40, 40, 250 });
	top_scroll_h->click_through = true;*/

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

	/*f (scroll->max_bar_v == scroll->moving_rect.h || !scroll->parent->enabled)
		top_scroll_v->enabled = false;
	else
		top_scroll_v->enabled = true;

	if (scroll->max_bar_h == scroll->moving_rect.w || !scroll->parent->enabled)
		top_scroll_h->enabled = false;
	else
		top_scroll_h->enabled = true;

	top_scroll_v->rect = { scroll->button_v->rect.x, scroll->button_v->rect.y, scroll->button_v->rect.w, scroll->button_v->rect.h };
	top_scroll_h->rect = { scroll->button_h->rect.x, scroll->button_h->rect.y, scroll->button_h->rect.w, scroll->button_h->rect.h };*/

	return true;
}

bool j1Console::CleanUp()
{
	return true;
}

void j1Console::Log(p2SString string)
{
	if (string.Length() > 0)
	{
		scroll->button_v->rect.y = scroll->max_bar_v - scroll->button_v->rect.h;

		UI_Text* text = new UI_Text();
		text->Set(iPoint(3, last_text_pos), App->font->default_15, 0, 255, 255, 255);
		text->SetText(string.GetString());
		scroll->AddElement(text);
		last_text_pos += TEXT_DISTANCE;
	}
}

void j1Console::LoadLogs()
{
	//Log("Welcome to the console");
	for (int i = 0; i < App->logs.count(); i++)
	{
		Log(App->logs[i].GetString());
	}
	App->logs.clear();	
}
