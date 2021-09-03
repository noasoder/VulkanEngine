#pragma once

#include "Vulkan.h"
#include "Utility/Matrix4.h"

class Vec3;

class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(0, 0, 1), const glm::quat& rot = glm::quat(1.0, 0.0, 0.0, 0.0),
			const glm::vec3& scale = glm::vec3(1.0));

	glm::mat4 GetMatrix();
	glm::vec3 GetAt();
	glm::vec3 GetUp();

	void RotateLocal(const double& xx, const double& yy, const double& zz, const double& a);
	void RotateWorld(const double& xx, const double& yy, const double& zz, const double& a);
	void TranslateWorld(glm::vec3 move);
	void TranslateLocal(glm::vec3 move);

	glm::quat RotateTowards(glm::quat q2, float maxAngle);

	glm::vec3 m_pos;
	glm::quat m_rot;
	glm::vec3 m_scale;
private:
};

