#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "p2Defs.h"
#include "p2List.h"
#include "j1Render.h"

float AngleFromTwoPoints(int x1, int y1, int x2, int y2);

int SmoothMovement(int value, int destination, float speed, float dt = 1.0f);

void LoadAnimationFromXML(p2List<SDL_Rect>& rects, const char* file, const char* animation_name);

#endif //__FUNCTIONS_H__