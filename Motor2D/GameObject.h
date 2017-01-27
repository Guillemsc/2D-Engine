#ifndef _GAMEOBJECT__H__
#define _GAMEOJBECT__H__

#include "p2Defs.h"
#include "j1Render.h"

class Animator;
class PhysBody;
class Animation;
enum body_type;
class GameObject
{
public:
	GameObject(iPoint pos);
	~GameObject();

	iPoint GetPos();
	void SetPos(iPoint pos);
	void AddAnimation(Animation* animation);
	void SetAnimation(const char* animation);

	void CreateCollision(body_type type, int width, int height, int cat, int mask);
	void CreateCollision(body_type type,int radius, int cat, int mask);
	void CreateStaticCollision(body_type type,int width, int height, int cat, int mask);
	void CreateStaticCollision(body_type type, int radius, int cat, int mask);
	void CreateSensorCollision(body_type type,int width, int height, int cat, int mask);
	void CreateSensorCollision(body_type type, int radius, int cat, int mask);

public:
	Animator*	    animator = nullptr;
	PhysBody*       pbody = nullptr;
	SDL_Texture*    texture = nullptr;

private:
	iPoint          pos = NULLPOINT;
};

#endif