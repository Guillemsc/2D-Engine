#include "j1Entity.h"
#include "Player.h"
#include "p2Log.h"

j1Entity::j1Entity()
{
}

j1Entity::~j1Entity()
{
}

bool j1Entity::Awake(pugi::xml_node &)
{
	bool ret = true;


	return ret;
}

bool j1Entity::Start()
{
	bool ret = true;

	return ret;
}

bool j1Entity::PreUpdate()
{
	bool ret = true;

	for (int i = 0; i < entity_list.count(); i++)
		ret = entity_list[i]->PreUpdate();

	return ret;
}

bool j1Entity::Update(float dt)
{
	bool ret = true;

	for (int i = 0; i < entity_list.count(); i++)
	{
		ret = entity_list[i]->Update(dt);
		entity_list[i]->Draw(dt);
	}

	return ret;
}

bool j1Entity::PostUpdate()
{
	bool ret = true;

	for (int i = 0; i < entity_list.count(); i++)
		ret = entity_list[i]->PostUpdate();

	return ret;
}

bool j1Entity::CleanUp()
{
	bool ret = true;

	for (int i = 0; i < entity_list.count(); i++)
		ret = entity_list[i]->CleanUp();

	return ret;
}

void j1Entity::OnCollision(PhysBody * bodyA, PhysBody * bodyB, b2Fixture * fixtureA, b2Fixture * fixtureB)
{
	for (int i = 0; i < entity_list.count(); i++)
		entity_list[i]->OnColl(bodyA, bodyB, fixtureA, fixtureB);
}

Entity* j1Entity::CreateEntity(entity_name entity)
{
	Entity* ret = nullptr;

	switch (entity)
	{
	case player:
		ret = new Player();
		break;
	default:
		break;
	}

	if (ret != nullptr)
	{
		ret->Start();
		entity_list.add(ret);
	}
	else
		LOG("Entity creation returned nullptr");

	return ret;
}

void j1Entity::DeleteEntity(Entity* entity)
{
	entity->CleanUp();
	entity_list.del(entity_list.At(entity_list.find(entity)));
	RELEASE(entity);
}



