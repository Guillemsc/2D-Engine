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

	PhysBody* b = App->physics->CreateStaticRectangle(0, 600, 1000, 50, 1, 1, 0, CATEGORY_SCENERY, MASK_SCENERY);
	b->type = pbody_type::p_t_world;
	b->listener = App->scene;

	go = new GameObject(iPoint(300, 300), CATEGORY_PLAYER, MASK_PLAYER, pbody_type::p_t_null);
	go->CreateCollision(iPoint(0, 0), 38, 80, fixture_type::f_t_null);
	go->CreateCollision(iPoint(0, -50), 20, fixture_type::f_t_down_ball);
	go->CreateCollision(iPoint(0, 50), 20, fixture_type::f_t_null);
	go->SetListener(App->scene);



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

void MainScene::OnColl(PhysBody * bodyA, PhysBody * bodyB, b2Fixture * fixtureA, b2Fixture * fixtureB)
{
}

