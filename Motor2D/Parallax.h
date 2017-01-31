#ifndef __PARALLAX_H__
#define __PARALLAX_H__

#include "j1Render.h"
#include "j1Scene.h"

class Parallax
{
	Parallax(SDL_Texture* texture, SDL_Rect rect, float speed);
	~Parallax();

public:
	void Update(float dt, iPoint target_pos);

private:
	float speed = 0.0f;
};

#endif !_PARALLAX_H__