#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

float AngleFromTwoPoints(int x1, int y1, int x2, int y2);

int SmoothMovement(int value, int destination, float speed, float dt = 1.0f);

#endif //__FUNCTIONS_H__