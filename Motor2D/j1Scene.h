#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "j1Gui.h"
#include "Scene.h"

struct SDL_Texture;
class MainScene;

struct layer_blit
{
	layer_blit() {};
	layer_blit(SDL_Texture* _texture, iPoint _pos, const SDL_Rect _section, float _speed, double _angle, int _pivot_x, int _pivot_y) 
	{
		texture = _texture; 
		pos = _pos; 
		section.x = _section.x;  section.y = _section.y; section.w = _section.w; section.h = _section.h;
		speed = _speed;
		angle = _angle;
		pivot_x = _pivot_x;
		pivot_y = _pivot_y;
	};

	SDL_Texture* texture = nullptr;
	iPoint pos; 
	SDL_Rect section = NULLRECT;
	float speed = 0.0f; 
	double angle = 0; 
	int pivot_x = 0;
	int pivot_y = 0;
};

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

	// Change scene
	void ChangeScene(Scene* new_scene);

	// Blit choosing the layer
	void LayerBlit(int layer, SDL_Texture* texture, iPoint pos, const SDL_Rect section = NULLRECT, float speed = 1.0f, double angle = 0, int pivot_x = INT_MAX, int pivot_y = INT_MAX);
	
private:
	void DoLayerBlit();

public:

private:
	// Layer Blit list
	p2PQueue<layer_blit> layer_list;

	// Current scene
	Scene*      current_scene = nullptr;

	MainScene*  main_scene = nullptr;



	
};

#endif // __j1SCENE_H__