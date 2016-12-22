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
	window = (UI_Window*)App->gui->UI_CreateWin(iPoint(App->render->camera.x, App->render->camera.y), 
			 App->render->camera.x + App->render->camera.w, CONSOLE_HEIGHT, true);
	window->always_top = true;
	window->CreateColoredRect(iPoint(window->rect.x, window->rect.y), window->rect.w, window->rect.h, { 40, 0, 0, 150 });


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
