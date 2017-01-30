#ifndef _PLAYER_
#define _PLAYER_

#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	~Player();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void OnColl(PhysBody* bodyA, PhysBody* bodyB, b2Fixture* fixtureA, b2Fixture* fixtureB);
};

#endif