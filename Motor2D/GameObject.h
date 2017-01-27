#ifndef _GAMEOBJECT__H__
#define _GAMEOJBECT__H__

#include "p2Defs.h"
#include "j1Render.h"

class Animator;
class PhysBody;
class GameObject
{
public:
	GameObject(iPoint pos);
	~GameObject();

	iPoint GetPos();
	void SetPos(iPoint pos);
	void SetAnimation(const char* animation);

	void CreateCollision(int width, int height, int cat, int mask);
	void CreateCollision(int radius, int cat, int mask);
	void CreateStaticCollision(int width, int height, int cat, int mask);
	void CreateStaticCollision(int radius, int cat, int mask);
	void CreateSensorCollision(int width, int height, int cat, int mask);
	void CreateSensorCollision(int radius, int cat, int mask);

public:
	Animator*	    animator = nullptr;
	PhysBody*       pbody = nullptr;
	SDL_Texture*    texture = nullptr;

private:
	iPoint          pos = NULLPOINT;
};

#endif