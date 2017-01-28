#include "j1Entity.h"
#include "Player.h"

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

	for (int i = 0; i < entity_list.count(); i++)
		ret = entity_list[i]->Start();

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
		ret = entity_list[i]->Update(dt);

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
		entity_list.add(ret);

	return ret;
}

