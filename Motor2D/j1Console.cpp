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
#define FRAMES_SIZE 5

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
	console_color = { 32, 32, 32, 150 };

	window = (UI_Window*)App->gui->UI_CreateWin(iPoint(App->render->camera.x, App->render->camera.y), 
			 App->render->camera.x + App->render->camera.w, CONSOLE_HEIGHT, true);
	window->always_top = true;

	colored_rect1 = (UI_ColoredRect*)window->CreateColoredRect(iPoint(window->rect.x, window->rect.y), window->rect.w, window->rect.h, console_color);
	colored_rect_top = (UI_ColoredRect*)window->CreateColoredRect(iPoint(window->rect.x, window->rect.y), window->rect.w, 30, { 32, 32, 32, 255 });
	colored_rect_left = (UI_ColoredRect*)window->CreateColoredRect(iPoint(window->rect.x, window->rect.y), FRAMES_SIZE, CONSOLE_HEIGHT, { 32, 32, 32, 255 });
	colored_rect_right = (UI_ColoredRect*)window->CreateColoredRect(iPoint(window->rect.x + window->rect.w - FRAMES_SIZE, window->rect.y), FRAMES_SIZE, CONSOLE_HEIGHT, { 32, 32, 32, 255 });
	colored_rect_bottom = (UI_ColoredRect*)window->CreateColoredRect(iPoint(window->rect.x, CONSOLE_HEIGHT - FRAMES_SIZE), window->rect.w, FRAMES_SIZE, { 32, 32, 32, 255 });

	top_text = (UI_Text*)window->CreateText(iPoint(10, 4), App->font->default_15);
	top_text->SetText("Console");

	return true;
}

bool j1Console::Update()
{
	return true;
}

bool j1Console::CleanUp()
{
	return true;
}
