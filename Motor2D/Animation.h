#ifndef _ANIMATION__H__
#define _ANIMATION__H__

#include "p2List.h"
#include "j1App.h"
#include "j1Textures.h"
#include "SDL\include\SDL.h"

struct SDL_Texture;

class Animation
{
public:
	Animation(p2List<SDL_Rect>& rects, float speed, bool loop = true);
	~Animation();

	SDL_Rect& GetAnimationFrame();
	SDL_Rect& GetActualFrame();
	float GetFrameIndex() const;
	SDL_Rect& GetFrame(int frame);
	void SetCurrFrame(int frame);
	void SetSpeed(float speed);
	void SetLoop(bool loop);
	bool IsCurrFrame(int frame);
	bool Finished() const;
	void Reset();

private:
	float			    speed = 0.0f;
	bool			    loop = false;
	int				    loops = 0;
	p2List<SDL_Rect>    frames;
	float			    curr_frame = 0.0f;
	p2SString			name;
};

class Animator
{
	Animator();
	~Animator();
};

#endif // !_ANIMATION__H__