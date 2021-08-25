#pragma once

#include "Vulkan.h"
#include "Utility/Matrix4.h"

class Vec3;

class Transform : public Matrix4
{
public:
	Vec3 GetWorldRotation();

private:
};

