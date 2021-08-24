#pragma once

#include "Vulkan.h"
#include "Matrix4.h"

class Vec3;

class Transform : public Matrix4
{
public:
	Vec3 GetWorldRotation();

private:
};

