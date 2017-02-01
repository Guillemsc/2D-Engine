#include "Animation.h"
#include "Functions.h"

Animation::Animation(const char* _name, p2List<SDL_Rect>& rects, float speed, bool loop) : speed(speed), loop(loop)
{
	for (p2List_item<SDL_Rect>* rect = rects.start; rect != nullptr; rect = rect->next)
		frames.add(rect->data);

	name.create("%s", _name);
}

Animation::~Animation()
{
}

SDL_Rect& Animation::GetAnimationFrame(float dt)
{
	curr_frame += (speed * dt);

	if (curr_frame >= frames.count())
	{
		if (loop)
			curr_frame = frames.count() - 1;
		else
			curr_frame = 0.0f;

		loops++;
	}

	return frames[(int)floor(curr_frame)];
}

SDL_Rect& Animation::GetActualFrame()
{
	return frames[(int)curr_frame];
}

float Animation::GetFrameIndex() const
{
	return (int)curr_frame;
}

SDL_Rect & Animation::GetFrame(int frame)
{
	return frames[frame];
}

void Animation::SetCurrFrame(int frame)
{
	curr_frame = frame;
}

void Animation::SetSpeed(float _speed)
{
	speed = _speed;
}

void Animation::SetLoop(bool _loop)
{
	loop = _loop;
}

bool Animation::IsCurrFrame(int frame)
{
	return (frame == curr_frame);
}

bool Animation::Finished() const
{
	return loops > 0;
}

void Animation::Reset()
{
	curr_frame = 0.0f;
	loops = 0;
}

const char* Animation::GetName()
{
	return name.GetString();
}

Animator::Animator()
{
	for (int i = 0; i < animations.count(); i++)
		delete animations[i];
}

Animator::~Animator()
{
}

void Animator::AddAnimation(Animation* animation)
{
	animations.add(animation);
}

void Animator::SetAnimation(const char* name)
{
	for (int i = 0; i < animations.count(); i++)
	{
		if (TextCmp(name, animations[i]->GetName()))
		{
			current_animation = animations[i];
			break;
		}
	}
}

Animation* Animator::GetAnimation(const char * name)
{
	Animation* ret = nullptr;

	for (int i = 0; i < animations.count(); i++)
	{
		if (TextCmp(name, animations[i]->GetName()))
		{
			ret = animations[i];
			break;
		}
	}

	return ret;
}
