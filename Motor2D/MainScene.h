#ifndef _MAINSCENE_H_
#define _MAINSCENE_H_

#include "Scene.h"

class GameObject;
class b2Fixture;

class MainScene : public Scene {
public:
	MainScene();
	~MainScene();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void OnColl(PhysBody* bodyA, PhysBody* bodyB, b2Fixture* fixtureA, b2Fixture* fixtureB);

	GameObject* go = nullptr;

private:

};


#endif // !_MAINSCENE_H_