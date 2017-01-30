#include "GameObject.h"
#include "j1Physics.h"
#include "Animation.h"
#include "p2Defs.h"
#include "j1Physics.h"
#include "Functions.h"

GameObject::GameObject(iPoint pos, int _cat, int _mask, float _gravity_scale, float _density, float _friction) : gravity_scale(_gravity_scale), density(_density), friction(_friction), cat(_cat), mask(_mask)
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

// Inputs a position in pixels and changes the position of the body
void GameObject::SetPos(iPoint new_pos)
{
	pbody->body->SetTransform(b2Vec2(PIXEL_TO_METERS(new_pos.x), PIXEL_TO_METERS(new_pos.y)), pbody->body->GetAngle());
}

// Inputs rotation in degrees and rotates de body
void GameObject::SetRotation(float angle)
{
	pbody->body->SetTransform(b2Vec2(pbody->body->GetPosition().x, pbody->body->GetPosition().y), DEGTORAD * angle);
}

void GameObject::SetMass(float mass)
{
	gravity_scale = mass;
}

void GameObject::SetFixedRotation(bool set)
{
	pbody->body->SetFixedRotation(set);
}

void GameObject::SetDynamic()
{
	pbody->body->SetType(b2_dynamicBody);
}

void GameObject::SetKinematic()
{
	pbody->body->SetType(b2_kinematicBody);
}

void GameObject::SetListener(j1Module * scene)
{
	pbody->listener = scene;
}



void GameObject::AddAnimation(Animation* animation)
{
	animator->AddAnimation(animation);
}

void GameObject::SetAnimation(const char * animation)
{
	animator->SetAnimation(animation);
}

void GameObject::CreateCollision(iPoint offset, int width, int height, fixture_type type)
{
	App->physics->AddRectangleToBody(pbody, offset.x, offset.y, width, height, type, density, 0, friction);
}

void GameObject::CreateCollision(iPoint offset, int rad, fixture_type type)
{
	App->physics->AddCircleToBody(pbody, offset.x, offset.y, rad, type, density, 0, friction);
}

void GameObject::CreateCollisionSensor(iPoint offset, int width, int height)
{
	App->physics->AddRectangleSensorToBody(pbody, offset.x, offset.y, width, height, density, 0, friction);
}


