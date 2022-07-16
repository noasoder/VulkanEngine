#pragma once

#include <cmath>
#include "Types.h"

#define HALF_PI			3.14159265359 * 0.5
#define PI              3.14159265359
#define TWO_PI          3.14159265359 * 2.0
#define GOLDEN_RATIO    1.61803398875

#define BILLION  1000000000L
#define MILLION  1000000


float Dot(Vec3 rVec1, Vec3 rVec2);

//returns random number between min and max (inclusive)
float Random(float min = 0.f, float max = 1.f);
//returns random number between min and max (inclusive)
int Random(int min = 0, int max = 1);