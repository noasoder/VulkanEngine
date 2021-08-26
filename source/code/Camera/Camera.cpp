
#include "Camera.h"

#include "glm/gtx/matrix_operation.hpp"
#include "Utility/Types.h"
#include "Utility/Maths.h"

Camera::Camera(Vec3 Pos, Vec3 LookAt, int FOV, float Aspect, float Near, float Far)
{
	Translate(Pos);
	//todo rotation
	//Rotate(PI, HALF_PI);
	m_fov = FOV;
	m_aspect = Aspect;
	m_near = Near;
	m_far = Far;
}

Camera::~Camera()
{

}

glm::mat4 Camera::GetView()
{
	Vec3 pos = GetWorldPosition();
	Vec3 lookAt = GetLookAt();
	Vec3 at = pos + lookAt;
	//Vec3 at = pos + GetRotation();
	//Vec3 at = pos + Vec3(0, 1, 0);

	//printf("at: X: %f Y: %f Z: %f\n", at.x, at.y, at.z);

	return glm::lookAt(glm::vec3(pos.x, pos.y, pos.z), glm::vec3(at.x, at.y, at.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Camera::UpdateAspect(float a)
{
	m_aspect = a;
}

glm::mat4 Camera::GetProj()
{
	return glm::perspective(glm::radians((float)m_fov), m_aspect, m_near, m_far);
}