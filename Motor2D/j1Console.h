#ifndef __j1CONSOLE_H__
#define __j1CONSOLE_H__

#include "j1Module.h"
#include "p2Point.h"

class UI_Window;

class j1Console : public j1Module
{
public:

	j1Console();

	// Destructor
	virtual ~j1Console();

	// Called before render is available
	bool Awake(pugi::xml_node& node);

	bool Start();

	bool Update();

	// Called before quitting
	bool CleanUp();

private:

public:

private:
	UI_Window* window = nullptr;

};

#endif // __j1CONSOLE_H__