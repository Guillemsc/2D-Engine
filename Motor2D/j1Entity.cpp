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

	for (p2List_item<Entity*>* current = entity_list.start; current != nullptr; current = current->next)
		ret = current->data->PreUpdate();

	return ret;
}

bool j1Entity::Update(float dt)
{
	bool ret = true;

	for (p2List_item<Entity*>* current = entity_list.start; current != nullptr; current = current->next)
	{
		ret = current->data->Update(dt);
		current->data->Draw(dt);
	}

	return ret;
}

bool j1Entity::PostUpdate()
{
	bool ret = true;

	for (p2List_item<Entity*>* current = entity_list.start; current != nullptr; current = current->next)
		ret = current->data->PostUpdate();

	return ret;
}

bool j1Entity::CleanUp()
{
	bool ret = true;

	for (p2List_item<Entity*>* current = entity_list.start; current != nullptr; current = current->next)
		ret = current->data->CleanUp();

	return ret;
}

void j1Entity::OnCollision(PhysBody * bodyA, PhysBody * bodyB, b2Fixture * fixtureA, b2Fixture * fixtureB)
{
	for (p2List_item<Entity*>* current = entity_list.start; current != nullptr; current = current->next)
		current->data->OnColl(bodyA, bodyB, fixtureA, fixtureB);
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
		ret->LoadEntity();
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



