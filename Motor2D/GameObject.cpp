#include "GameObject.h"
#include "j1Physics.h"
#include "Animation.h"
#include "p2Defs.h"
#include "j1Physics.h"

GameObject::GameObject(iPoint _pos, float mass, int _cat, int _mask) : pos(_pos), gravity_scale(mass), cat(_cat), mask(_mask)
{
	animator = new Animator();
	pbody = App->physics->CreateCircleSensor(pos.x, pos.y, 5, 1, mass);
	pbody->body->SetType(b2_dynamicBody);
}

GameObject::~GameObject()
{
}

iPoint GameObject::GetPos()
{
	iPoint ret = NULLPOINT;

	pbody->GetPosition(ret.x, ret.y);

	return ret;
}

void GameObject::SetPos(iPoint new_pos)
{
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

void GameObject::SetMass(float mass)
{
	gravity_scale = mass;
}

void GameObject::CreateCollision(body_type type, int width, int height, int offset_x, int offset_y)
{
	PhysBody* pb = App->physics->CreateRectangle(GetPos().x + offset_x, GetPos().y + offset_y, width, height, 1, gravity_scale, 0, cat, mask);
	pb->type = type;
	AddCollision(pb);
}

void GameObject::AddCollision(PhysBody * _pbody)
{
	PhysBody* to_atach = nullptr;

	if (pbodies.count() == 0)
		to_atach = pbody;
	else
		to_atach = pbodies.end->data;

	int x1, y1, x2, y2;
	to_atach->GetPosition(x1, y1);
	_pbody->GetPosition(x2, y2);

	int distance_x = x2 - x1;
	int distance_y = y2 - y1;

	_pbody->body->SetGravityScale(gravity_scale);
	pbodies.add(_pbody);
	joints.add(App->physics->CreateWeldJoint(to_atach, _pbody, PIXEL_TO_METERS(distance_x), PIXEL_TO_METERS(distance_y)));
}

