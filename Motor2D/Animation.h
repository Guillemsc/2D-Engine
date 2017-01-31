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
	Animation(const char* name, p2List<SDL_Rect>& rects, float speed, bool loop = true);
	~Animation();

	// Gets the animation frame adding speed
	SDL_Rect& GetAnimationFrame(float dt);

	// Get the current animation frame
	SDL_Rect& GetActualFrame();

	// Get the current fame index
	float GetFrameIndex() const;

	// Get the current frame rect
	SDL_Rect& GetFrame(int frame);

	// Set the current frame
	void SetCurrFrame(int frame);

	// Set the frame speed
	void SetSpeed(float speed);

	// Set if the animation loops
	void SetLoop(bool loop);

	// Checks if it's the current frame
	bool IsCurrFrame(int frame);

	// Checks if the animation has finished
	bool Finished() const;

	// Resets the animation
	void Reset();

	// Returns the animation name
	const char* GetName();

public:

private:
	p2SString			name;
	float			    speed = 0.0f;
	bool			    loop = false;
	int				    loops = 0;
	p2List<SDL_Rect>    frames;
	float			    curr_frame = 0.0f;
};

class Animator
{
public:
	Animator();
	~Animator();

	// Add an animation
	void AddAnimation(Animation* animation);

	// Set a current animation
	void SetAnimation(const char* name);

	// Returns the animation using the name
	Animation* GetAnimation(const char* name);

private:  
	Animation*           current_animation = nullptr;
	p2List<Animation*>   animations;

};

#endif // !_ANIMATION__H__