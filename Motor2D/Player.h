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
};

#endif