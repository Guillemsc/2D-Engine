#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "p2Defs.h"
#include "p2List.h"
#include "j1Render.h"

float AngleFromTwoPoints(float x1, float y1, float x2, float y2);
float DistanceFromTwoPoints(float x1, float y1, float x2, float y2);

bool TextCmp(const char* text1, const char* text2);

int SmoothMovement(int value, int destination, float speed, float dt = 1.0f);

void LoadAnimationFromXML(p2List<SDL_Rect>& rects, const char* file, const char* animation_name);

#endif //__FUNCTIONS_H__