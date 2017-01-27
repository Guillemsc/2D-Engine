#include "Functions.h"
#include <stdio.h>
#include <cmath>
#include "p2Defs.h"

// Returns the angle between two points in degrees
float AngleFromTwoPoints(int x1, int y1, int x2, int y2)
{
	float deltaY = y2 - y1;
	float deltaX = x2 - x1;

	return (atan2(deltaY, deltaX) * RADTODEG);
}