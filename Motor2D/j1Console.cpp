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

#define CONSOLE_HEIGHT 200
#define TOP_FRAME_SIZE 30
#define FRAMES_SIZE 5
#define SCROLL_BUTTON_SIZE 15
#define TEXT_DISTANCE 20

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

	bottom_scroll = (UI_ColoredRect*)window->CreateColoredRect(iPoint(scroll->button->rect.x, scroll->min_bar), scroll->button->rect.w, scroll->rect.h, {60, 60, 60, 200});
	bottom_scroll->click_through = true;
	top_scroll = (UI_ColoredRect*)window->CreateColoredRect(iPoint(scroll->button->rect.x, scroll->button->rect.y), scroll->button->rect.w, scroll->button->rect.h, { 40, 40, 40, 250 });
	top_scroll->click_through = true;

	return true;
}

bool j1Console::PreUpdate()
{
	if (one_time)
	{
		Log("Welcome to the console");
		for (int i = 0; i < App->logs.count(); i++)
		{
			Log(App->logs[i].GetString());
		}
		one_time = false;
	}

	return true;
}

bool j1Console::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_GRAVE) == KEY_DOWN)
	{
		window->SetEnabledAndChilds(!window->enabled);
	}

	if (scroll->max_bar == scroll->moving_rect.h)
		top_scroll->enabled = false;
	else
		top_scroll->enabled = true;

	top_scroll->rect = { scroll->button->rect.x, scroll->button->rect.y, scroll->button->rect.w, scroll->button->rect.h };

	return true;
}

bool j1Console::CleanUp()
{
	return true;
}

void j1Console::Log(p2SString string)
{
	if (string.Length() > 1)
	{
		scroll->button->rect.y = scroll->max_bar - scroll->button->rect.h;

		UI_Text* text = new UI_Text();
		text->Set(iPoint(3, last_text_pos), App->font->default_15, 0, 255, 255, 255);
		text->SetText(string.GetString());
		scroll->AddElement(text);
		last_text_pos += TEXT_DISTANCE;
	}
}
