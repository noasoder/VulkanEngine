#pragma once

#include "Vulkan.h"
#include "Types.h"

class Transform
{
public:
	Transform(const Vec3& pos = Vec3(0, 0, 1), const glm::quat& rot = glm::quat(1.0, 0.0, 0.0, 0.0),
			const Vec3& scale = Vec3(1.0));

	glm::mat4 GetMatrix();
	Vec3 GetAt();
	Vec3 GetUp();

	void RotateLocal(const double& xx, const double& yy, const double& zz, const double& a);
	void RotateWorld(const double& xx, const double& yy, const double& zz, const double& a);
	void TranslateWorld(Vec3 move);
	void TranslateLocal(Vec3 move);

	// glm::quat RotateTowards(glm::quat q2, float maxAngle);

	Vec3 m_pos;
	glm::quat m_rot;
	Vec3 m_scale;
private:
};

