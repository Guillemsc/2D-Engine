#include "GameObject.h"
#include "j1Physics.h"
#include "Animation.h"



GameObject::GameObject(iPoint _pos) : pos(_pos)
{
	animator = new Animator();
}

GameObject::~GameObject()
{
}

iPoint GameObject::GetPos()
{
	iPoint ret = NULLPOINT;

	if (pbody != nullptr)
		pbody->GetPosition(ret.x, ret.y);
	else
		ret = pos;

	return ret;
}

void GameObject::SetPos(iPoint new_pos)
{
	if (pbody != nullptr)
		pbody->body->SetTransform(b2Vec2(new_pos.x, new_pos.y), pbody->body->GetAngle());

	pos = new_pos;
}

void GameObject::AddAnimation(Animation* animation)
{
	if (animator != nullptr)
		animator->AddAnimation(animation);
}

void GameObject::SetAnimation(const char * animation)
{
	if (animator != nullptr)
		animator->SetAnimation(animation);
}

void GameObject::CreateCollision(body_type type, int width, int height, int cat, int mask)
{
	pbody = App->physics->CreateRectangle(pos.x, pos.y, width, height, 0.0f, cat, mask);
	pbody->type = type;
}

void GameObject::CreateCollision(body_type type, int radius, int cat, int mask)
{
	pbody = App->physics->CreateCircle(pos.x, pos.y, radius, 0.0f, cat, mask);
	pbody->type = type;
}

void GameObject::CreateStaticCollision(body_type type, int width, int height, int cat, int mask)
{
	pbody = App->physics->CreateStaticRectangle(pos.x, pos.y, width, height, 0.0f, cat, mask);
	pbody->type = type;
}

void GameObject::CreateStaticCollision(body_type type, int radius, int cat, int mask)
{
	pbody = App->physics->CreateStaticCircle(pos.x, pos.y, radius, 0.0f, cat, mask);
	pbody->type = type;
}

void GameObject::CreateSensorCollision(body_type type, int width, int height, int cat, int mask)
{
	pbody = App->physics->CreateRectangleSensor(pos.x, pos.y, width, height, 0.0f, cat, mask);
}

void GameObject::CreateSensorCollision(body_type type, int radius, int cat, int mask)
{
	pbody = App->physics->CreateCircleSensor(pos.x, pos.y, radius, 0.0f, cat, mask);
}
