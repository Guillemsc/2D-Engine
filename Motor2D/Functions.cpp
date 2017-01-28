#include "Functions.h"
#include "j1App.h"
#include <stdio.h>
#include <cmath>
#include "p2Defs.h"
#include "p2Log.h"

// Returns the angle between two points in degrees
float AngleFromTwoPoints(int x1, int y1, int x2, int y2)
{
	float deltaY = y2 - y1;
	float deltaX = x2 - x1;

	return (atan2(deltaY, deltaX) * RADTODEG);
}

int SmoothMovement(int value, int destination, float speed, float dt)
{
	int ret = value;

	int distance = destination - value;

	if (abs(distance) > 0)
	{
		//int to_add = floor((speed * dt) * distance);
		float to_add = (speed * (distance ^ 2));
		ret = value + ceil(to_add * dt);
		//LOG("%f %f", to_add * dt, dt);
	}

	return ret;
}

void LoadAnimationFromXML(p2List<SDL_Rect>& rects, const char * file, const char* animation_name)
{
	pugi::xml_document doc;
	pugi::xml_node node;

	App->LoadXML(file, doc);

	node = doc.child("file").child("animations").child(animation_name);

	for (pugi::xml_node curr = node.child("rect"); curr != nullptr; curr = curr.next_sibling("rect"))
	{
		SDL_Rect rect;
		rect.x = curr.attribute("x").as_int();
		rect.y = curr.attribute("y").as_int();
		rect.w = curr.attribute("w").as_int();
		rect.h = curr.attribute("h").as_int();
		rects.add(rect);
	}
}
