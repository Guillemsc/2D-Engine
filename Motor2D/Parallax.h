#ifndef __PARALLAX_H__
#define __PARALLAX_H__

#include "j1Render.h"
#include "j1Scene.h"

class Parallax
{
public:
	Parallax(int layer, fPoint pos, SDL_Texture* texture, SDL_Rect rect, float speed);
	~Parallax();

	void Update(float dt, fPoint target_pos);

private:
	int GetLeftChunk();
	int GetRightChunk();

private:
	bool start = true;

	float speed = 0.0f;
	int layer = 0;

	p2List<fPoint> chunks;

	fPoint target = NULLPOINT;
	int distance = 0;

	SDL_Texture* texture = nullptr;
	SDL_Rect rect = NULLRECT;
};

#endif !_PARALLAX_H__