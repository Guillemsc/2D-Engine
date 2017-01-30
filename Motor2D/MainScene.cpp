#include "MainScene.h"
#include "j1Scene.h"
#include "p2Log.h"
#include "j1Input.h"
#include "Functions.h"
#include "j1Physics.h"
#include "GameObject.h"
#include "CollisionFilters.h"


MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

bool MainScene::Start()
{
	bool ret = true;

	LOG("Start MainScene");

	App->physics->CreateStaticRectangle(0, 600, 1000, 50, 1, 1, 0, CATEGORY_SCENERY, MASK_SCENERY);

	go = new GameObject(iPoint(300, 300), CATEGORY_PLAYER, MASK_PLAYER);
	go->CreateCollision(iPoint(0, 0), 38, 80);
	go->CreateCollision(iPoint(0, -50), 20);
	go->CreateCollision(iPoint(0, 50), 20);
	//go->CreateCollision(iPoint(0, -40), 20);
	//go->CreateCollision(iPoint(0, 40), 20);
	go->SetFixedRotation(true);



	return ret;
}

bool MainScene::PreUpdate()
{
	bool ret = true;


	return ret;
}

bool MainScene::Update(float dt)
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x++;
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x--;
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y++;
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y--;

	return ret;
}

bool MainScene::PostUpdate()
{
	bool ret = true;


	return ret;
}

bool MainScene::CleanUp()
{
	bool ret = true;


	return ret;
}
