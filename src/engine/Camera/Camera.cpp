
#include "Camera/Camera.h"

#include "glm/gtx/matrix_operation.hpp"
#include "Utility/Types.h"
#include "Utility/Maths.h"
//#include "Utility/Rotor3.h"

Camera::Camera(Vec3 Pos, Vec3 LookAt, int FOV, float Aspect, float Near, float Far)
{
	//m_pos = Pos;
	//Translate(Pos);
	//todo rotation
	//Rotate(PI, HALF_PI);
	m_fov = FOV;
	m_aspect = Aspect;
	m_near = Near;
	m_far = Far;

	//m_rotor = Rotor3(Bivector3(1, 1, 0), PI);
}

Camera::~Camera()
{

}

glm::mat4 Camera::GetView()
{
	//Vec3 pos = GetWorldPosition();
	//Vec3 lookAt = GetLookAt();
	//Vec3 at = pos + lookAt;
	//Vec3 at = pos + GetRotation();
	//Vec3 at = pos + Vec3(0, 1, 0);

	//printf("at: X: %f Y: %f Z: %f\n", at.x, at.y, at.z);

	//return glm::lookAt(glm::vec3(pos.x, pos.y, pos.z), glm::vec3(at.x, at.y, at.z), glm::vec3(0.0f, 0.0f, 1.0f));

	return glm::lookAt(m_pos, m_pos + GetAt(), GetUp());

	//Matrix4 mat = m_rotor.toMatrix4();
	//mat.m3 = Vec4(0, -2, 0, 1);
	//return mat.ToGlmMat4();
	
	//return ToGlmMat4();
}

void Camera::RotateCam(glm::vec3 rot, glm::vec3 speed)
{
	RotateLocal(rot.x, 0, 0, speed.x);
	RotateWorld(0, 0, rot.z, speed.z);
}

void Camera::UpdateAspect(float a)
{
	m_aspect = a;
}

glm::mat4 Camera::GetProj()
{
	return glm::perspective(glm::radians((float)m_fov), m_aspect, m_near, m_far);
}