#ifndef _MAINSCENE_H_
#define _MAINSCENE_H_

#include "Scene.h"

class MainScene : public Scene {
public:
	MainScene();
	~MainScene();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	//void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

private:

};


#endif // !_MAINSCENE_H_