#include "Functions.h"
#include "j1App.h"
#include <stdio.h>
#include <cmath>
#include "p2Defs.h"
#include "p2Log.h"

// Returns the angle between two points in degrees
float AngleFromTwoPoints(float x1, float y1, float x2, float y2)
{
	float deltaY = y2 - y1;
	float deltaX = x2 - x1;

	return (atan2(deltaY, deltaX) * RADTODEG);
}

float DistanceFromTwoPoints(float x1, float y1, float x2, float y2)
{
	int distance_x = x2 - x1;
	int distance_y = y2 - y1;
	float sign = ((distance_x * distance_x) + (distance_y * distance_y));
	float dist = abs((distance_x * distance_x) + (distance_y * distance_y));

	if(sign > 0)
		return sqrt(dist);
	else
		return -sqrt(dist);
}

bool TextCmp(const char * text1, const char * text2)
{
	bool ret = false;

	if (strcmp(text1, text2) == 0)
		ret = true;

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
