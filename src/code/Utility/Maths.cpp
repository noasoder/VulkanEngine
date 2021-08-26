#include "Maths.h"

#include "Utility/Types.h"

float Dot(Vec3 rVec1, Vec3 rVec2)
{
	float dot = 0.0f;

	dot = rVec1.x * rVec2.x + rVec1.y * rVec2.y + rVec1.z * rVec2.z;

	return dot;
}