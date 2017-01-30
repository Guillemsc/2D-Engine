#include "GameObject.h"
#include "j1Physics.h"
#include "Animation.h"
#include "p2Defs.h"
#include "j1Physics.h"
#include "Functions.h"

// --------------------------------
// --------------------------------
//			Game Object
// --------------------------------
// --------------------------------

// TO KEEP IN MIND:
// - The CATEGORY and the MASK are defined on CollisionFilters.h.  
// - pbody_type it's an enum that refeers to the PhysBodys.
// - fixture_type it's an enum that refeers to a b2Fixture from a PhysBody.
// - Both pbody and fixture _type are used to know what collides with what on the OnCollision method.
// - Both pbody and fixture _type are defined on CollisionFilters.h.  


GameObject::GameObject(iPoint pos, int _cat, int _mask, pbody_type pb_type, float _gravity_scale,  float _density, float _friction) : gravity_scale(_gravity_scale), density(_density), friction(_friction), cat(_cat), mask(_mask)
{
	animator = new Animator();
	pbody = App->physics->CreateCircleSensor(pos.x, pos.y, 5, _density, _gravity_scale, 0, cat, mask);
	pbody->body->SetType(b2_dynamicBody);
	pbody->type = pb_type;
}

GameObject::~GameObject()
{
	App->physics->DeleteBody(pbody);
}

// Gets position of the pbody in pixels
iPoint GameObject::GetPos()
{
	iPoint ret = NULLPOINT;

	pbody->GetPosition(ret.x, ret.y);

	return ret;
}

// Gets rotation of the pbody in degrees
float GameObject::GetRotation()
{
	return pbody->GetRotation();
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

// Fix rotation
void GameObject::SetFixedRotation(bool set)
{
	pbody->body->SetFixedRotation(set);
}

// Sets the body to b2_dynamicBody
void GameObject::SetDynamic()
{
	pbody->body->SetType(b2_dynamicBody);
}

// Sets the body to b2_kinematicBody
void GameObject::SetKinematic()
{
	pbody->body->SetType(b2_kinematicBody);
}

// Sets how much the body is affected by gravity
void GameObject::SetGravityScale(float _gravity_scale)
{
	pbody->body->SetGravityScale(_gravity_scale);
	gravity_scale = _gravity_scale;
}

// Sets listener module
void GameObject::SetListener(j1Module * scene)
{
	pbody->listener = scene;
}

// Changes cateogry and mask of the body
void GameObject::SetCatMask(int cat, int mask)
{
	b2Filter data;
	data.categoryBits = cat;
	data.maskBits = mask;
	pbody->body->GetFixtureList()->SetFilterData(data);
}

// Adds an animation
void GameObject::AddAnimation(Animation* animation)
{
	animator->AddAnimation(animation);
}

// Sets an animation
void GameObject::SetAnimation(const char * animation)
{
	animator->SetAnimation(animation);
}

// Adds a box shape to the current body
void GameObject::CreateCollision(iPoint offset, int width, int height, fixture_type type)
{
	App->physics->AddRectangleToBody(pbody, offset.x, offset.y, width, height, type, density, 0, friction);
}

// Adds a circle shape to the current body
void GameObject::CreateCollision(iPoint offset, int rad, fixture_type type)
{
	App->physics->AddCircleToBody(pbody, offset.x, offset.y, rad, type, density, 0, friction);
}

// Adds a box sensor shape to the current body
void GameObject::CreateCollisionSensor(iPoint offset, int width, int height, fixture_type type)
{
	App->physics->AddRectangleSensorToBody(pbody, offset.x, offset.y, width, height, type, density, 0, friction);
}

// Adds a circle sensor shape to the current body
void GameObject::CreateCollisionSensor(iPoint offset, int rad, fixture_type type)
{
	App->physics->AddCircleSensorToBody(pbody, offset.x, offset.y, rad, type, density, 0, friction);
}



