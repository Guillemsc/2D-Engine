#include "Player.h"
#include "GameObject.h"
#include "Scene.h"
#include "j1App.h"
#include "j1Input.h"
#include "CollisionFilters.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "Functions.h"
#include "j1Textures.h"


Player::Player()
{
}

Player::~Player()
{
}

bool Player::LoadEntity()
{
	bool ret = true;

	player_go = new GameObject(iPoint(300, 300), App->cf->CATEGORY_PLAYER, App->cf->MASK_PLAYER, pbody_type::p_t_null, 1);

	player_go->CreateCollision(iPoint(0, 0), 38, 80, fixture_type::f_t_null);
	player_go->CreateCollision(iPoint(0, -50), 20, fixture_type::f_t_down_ball);
	player_go->CreateCollision(iPoint(0, 50), 20, fixture_type::f_t_null);
	player_go->SetListener((j1Module*)App->scene);
	player_go->SetFixedRotation(true);

	player_go->SetTexture(App->tex->LoadTexture("data/spritesheet.png"));

	p2List<SDL_Rect> idle_rects;
	LoadAnimationFromXML(idle_rects, "player.xml", "idle");
	Animation* idle = new Animation("idle", idle_rects, 2.0f);
	player_go->AddAnimation(idle);

	player_go->SetAnimation("idle");

	return ret;
}

bool Player::Start()
{
	bool ret = true;



	return ret;
}

bool Player::PreUpdate()
{
	bool ret = true;



	return ret;
}

bool Player::Update(float dt)
{
	bool ret = true;

	float speed = (200 * dt);

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		player_go->SetPos({ player_go->fGetPos().x - speed, player_go->fGetPos().y });
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		player_go->SetPos({ player_go->fGetPos().x + speed, player_go->fGetPos().y });

	return ret;
}

bool Player::Draw(float dt)
{
	bool ret = true;

	App->scene->LayerBlit(2, player_go->GetTexture(), { player_go->GetPos().x - 40, player_go->GetPos().y - 67 }, player_go->GetCurrentAnimationRect(dt));

	return ret;
}

bool Player::PostUpdate()
{
	bool ret = true;



	return ret;
}

bool Player::CleanUp()
{
	bool ret = true;



	return ret;
}

void Player::OnColl(PhysBody * bodyA, PhysBody * bodyB, b2Fixture * fixtureA, b2Fixture * fixtureB)
{
}
