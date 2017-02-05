#include "Animation.h"
#include "Functions.h"
#include "p2Log.h"

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
		if (!loop)
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
	if (name.Length() > 0)
		return name.GetString();
	else
		return "";
}

Animator::Animator()
{
	for (p2List_item<Animation*>* current = animations.start; current != nullptr; current = current->next)
		delete current->data;
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
	if (next_animation != nullptr && TextCmp(next_animation->GetName(), name))
		return;

	for (p2List_item<Animation*>* current = animations.start; current!= nullptr; current = current->next)
	{
		if (TextCmp(name, current->data->GetName()))
		{
			next_animation = current->data;
			break;
		}
	}
}

void Animator::SetAnimationTransition(const char * transition_name, const char * a1, const char * a2)
{
	anim_trans at(transition_name, a1, a2);
	anim_trans_list.add(at);
}

Animation* Animator::GetAnimation(const char * name)
{
	Animation* ret = nullptr;

	for (p2List_item<Animation*>* current = animations.start; current != nullptr; current = current->next)
	{
		if (TextCmp(name, current->data->GetName()))
		{
			ret = current->data;
			break;
		}
	}

	return ret;
}

Animation* Animator::GetCurrentAnimation()
{
	for (p2List_item<anim_trans>* trans = anim_trans_list.start; trans != nullptr; trans = trans->next)
	{
		if (TextCmp(next_animation->GetName(), trans->data.a2.GetString()) && TextCmp(current_animation->GetName(), trans->data.a1.GetString()))
		{
			if (!GetAnimation(trans->data.transition_name.GetString())->Finished())
				return GetAnimation(trans->data.transition_name.GetString());
			else
				GetAnimation(trans->data.transition_name.GetString())->Reset();
		}
	}

	if(current_animation != next_animation || current_animation == nullptr || anim_trans_list.count() == 0)
		current_animation = next_animation;

	return current_animation;
}
