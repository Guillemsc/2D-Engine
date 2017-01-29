#ifndef _GAMEOBJECT__H__
#define _GAMEOJBECT__H__

#include "p2Defs.h"
#include "j1Render.h"
#include "p2List.h"

class Animator;
class PhysBody;
class b2Joint;
class Animation;

enum body_type;
class GameObject
{
public:
	GameObject(iPoint pos, float mass);
	~GameObject();

	iPoint GetPos();
	void SetPos(iPoint pos);
	void AddAnimation(Animation* animation);
	void SetAnimation(const char* animation);
	void AddCollision(body_type type, PhysBody* pbody);

public:
	Animator*	        animator = nullptr;
	SDL_Texture*        texture = nullptr;

private:
	iPoint              pos = NULLPOINT;
	float				gravity_scale = 0.0f;

	PhysBody*           pbody = nullptr;
	p2List<PhysBody*>   pbodies;
	p2List<b2Joint*>    joints;
};

#endif