
#include "Vulkan.h"

#include "Transform.h"
#include "Utility/Types.h"
//#include "Utility/Rotor3.h"

class Vec3;

class Camera : public Transform {
public:
	Camera(Vec3 Pos, Vec3 LookAt, int FOV, float Aspect, float Near, float Far);
	~Camera();

	glm::mat4 GetView();
	glm::mat4 GetProj();
	void UpdateAspect(float a);

	void RotateCam(glm::vec3 rot, glm::vec3 speed);

private:

	float m_fov;
	float m_aspect;
	float m_near;
	float m_far;
};