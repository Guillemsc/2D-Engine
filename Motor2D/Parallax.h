#ifndef __PARALLAX_H__
#define __PARALLAX_H__

#include "j1Render.h"
#include "j1Scene.h"

// -----------------------------------------
// -----------------------------------------

		    // PARALLAXXXXXX //

// -----------------------------------------
// -----------------------------------------

class Parallax
{
public:
	// -Layer refeers to the LayerBlit on the j1Scene
	// -Chunks is the amount of simultanious copies one next to the other
	// -Pos is the starting position of the image/s
	Parallax(int layer, int chunks, fPoint pos, SDL_Texture* texture, SDL_Rect rect, float speed);
	~Parallax();

	// Target_pos is the target that the parallax will follow. Ex: Main character
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
	int chunk_number = 0;

	SDL_Texture* texture = nullptr;
	SDL_Rect rect = NULLRECT;
};

#endif !_PARALLAX_H__