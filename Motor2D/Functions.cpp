#include "Functions.h"
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
		LOG("%f %f", to_add * dt, dt);
	}

	return ret;
}
