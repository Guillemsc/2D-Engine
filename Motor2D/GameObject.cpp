#include "GameObject.h"
#include "j1Physics.h"
#include "Animation.h"
#include "p2Defs.h"
#include "j1Physics.h"
#include "Functions.h"

GameObject::GameObject(iPoint pos, float _gravity_scale, float _density, int _cat, int _mask) : gravity_scale(_gravity_scale), cat(_cat), mask(_mask)
{
	animator = new Animator();
	pbody = App->physics->CreateCircleSensor(pos.x, pos.y, 5, _density, _gravity_scale, 0, cat, mask);
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

void GameObject::SetDynamic()
{
	for (int i = 0; i < pbodies.count(); i++)
		pbodies[i]->body->SetType(b2_dynamicBody);
}

void GameObject::CreateCollision(body_type type, int width, int height, int offset_x, int offset_y, float density)
{
	PhysBody* pb = App->physics->CreateRectangle(GetPos().x + (width/2) + offset_x, GetPos().y + (height/2) + offset_y, width, height, density, gravity_scale, 0, cat, mask);
	pb->type = type;
	AddCollision(pb);
}

void GameObject::AddCollision(PhysBody* _pbody)
{
	PhysBody* to_atach = nullptr;

	if (pbodies.count() == 0)
		to_atach = pbody;
	else
		to_atach = pbodies.end->data;

	int x1, y1, x2, y2;
	_pbody->GetPosition(x1, y1);
	to_atach->GetPosition(x2, y2);

	int distance_x = x2 - x1;
	int distance_y = y2 - y1;
	int angle = AngleFromTwoPoints(x1, y1, x2, y2);
	
	_pbody->body->SetGravityScale(gravity_scale);
	pbodies.add(_pbody);

	joints.add(App->physics->CreateAtachJoint(_pbody, to_atach, distance_x, distance_y, angle));
}

