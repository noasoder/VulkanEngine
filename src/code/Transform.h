#pragma once

#include "Vulkan.h"
#include "Utility/Matrix4.h"

class Vec3;

class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(0, -2, 0), const glm::quat& rot = glm::quat(1.0, 0.0, 0.0, 0.0),
			const glm::vec3& scale = glm::vec3(1.0));

	glm::mat4 GetMatrix();
	glm::vec3 GetAt();
	glm::vec3 GetUp();
	glm::quat CreateFromAxisAngle(const double& xx, const double& yy, const double& zz, const double& a);
	void Rotate(const double& xx, const double& yy, const double& zz, const double& a);

	glm::vec3 m_pos;
	glm::quat m_rot;
	glm::vec3 m_scale;
private:
};

