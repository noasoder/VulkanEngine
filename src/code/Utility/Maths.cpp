#include "Utility/Maths.h"

#include "Utility/Types.h"
#include <ctime>
#include <chrono>

float Dot(Vec3 rVec1, Vec3 rVec2)
{
	float dot = 0.0f;

	dot = rVec1.x * rVec2.x + rVec1.y * rVec2.y + rVec1.z * rVec2.z;

	return dot;
}

float Random(float min, float max)
{
	std::chrono::high_resolution_clock m_clock;
	double nanoSec = std::chrono::duration_cast<std::chrono::nanoseconds>(m_clock.now().time_since_epoch()).count();

	srand(nanoSec);
	float result = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	return result;
}

int Random(int min, int max)
{
	std::chrono::high_resolution_clock m_clock;
	double nanoSec = std::chrono::duration_cast<std::chrono::nanoseconds>(m_clock.now().time_since_epoch()).count();

	srand(nanoSec);
	int result = min + (rand() % (max - min + 1));
	return result;
}