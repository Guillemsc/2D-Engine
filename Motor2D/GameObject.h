#ifndef _GAMEOBJECT__H__
#define _GAMEOJBECT__H__

#include "p2Defs.h"
#include "j1Render.h"
#include "p2List.h"

class Animator;
class PhysBody;
class b2Joint;
class Animation;

enum class pbody_type;
enum class fixture_type;
class GameObject
{
public:
	GameObject(iPoint pos, int cat, int mask, pbody_type pb_type, float gravity_scale = 1.0f, float density = 1.0f, float friction = 1.0f);
	~GameObject();

	iPoint GetPos();
	void SetPos(iPoint pos);
	void SetRotation(float angle);
	void SetMass(float mass);
	void SetFixedRotation(bool set);
	void SetDynamic();
	void SetKinematic();
	void SetListener(j1Module* scene);

	void AddAnimation(Animation* animation);
	void SetAnimation(const char* animation);

	void CreateCollision(iPoint offset, int width, int height, fixture_type type);
	void CreateCollision(iPoint offset, int rad, fixture_type type);

	void CreateCollisionSensor(iPoint offset, int width, int height);
	//void CreateCollision(int radius, int offset_x, int offset_y);

private:


public:
	Animator*	        animator = nullptr;
	SDL_Texture*        texture = nullptr;

private:
	float				gravity_scale = 0.0f;
	float				density = 0.0f;
	float				friction = 0.0f;
	float               restitution = 0.0f;
	int					cat = 0;
	int					mask = 0;

	PhysBody*           pbody = nullptr;
};

#endif