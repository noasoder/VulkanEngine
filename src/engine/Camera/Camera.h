
#include "Core.h"

#include "Transform.h"
#include "Types.h"
//#include "Rotor3.h"

class Camera : public Transform {
public:
	Camera(Vec3 Pos, Vec3 LookAt, int FOV, float Aspect, float Near, float Far);
	~Camera();

	glm::mat4 GetView();
	glm::mat4 GetProj();
	void UpdateAspect(float a);

	void RotateCam(glm::vec3 rot, glm::vec3 speed);

private:

	int m_fov;
	float m_aspect;
	float m_near;
	float m_far;
};