#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "j1Gui.h"

struct SDL_Texture;
class GuiImage;
class GuiText;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	UI_Window* window1;
		UI_Image* background;
		UI_Image* blue_selector;
		UI_Image* red_selector;

		UI_Image* image_red;
		UI_Image* image_blue;

		SDL_Rect ryu;
		SDL_Rect honda;
		SDL_Rect blanka;
		SDL_Rect guile;

		SDL_Rect ken;
		SDL_Rect chunli;
		SDL_Rect zangief;
		SDL_Rect dhalsim;

	UI_Image* curr_selector = nullptr;

	SDL_Rect box_borders;

	//UI_Window* window2;
	//UI_Button* button3;
	//UI_Text_Input* input1; 
	//UI_Text_Input* input2;
	//UI_Scroll_Bar* scroll1;

	//UI_Text* text1;
	//UI_Text* text2;
	//UI_Image* image1;
	//UI_Button* button1;
	//UI_Button* button2;

private:
	SDL_Texture* debug_tex;
	GuiImage* banner;
	GuiText* text;
};

#endif // __j1SCENE_H__