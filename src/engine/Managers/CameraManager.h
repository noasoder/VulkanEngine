#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include <vector>
#include "Types.h"

class Camera;
class CameraController;

namespace CameraManager
{
	void Init();
	void Destroy();

	void Update(float DeltaTime);

	Camera* GetCurrentCamera();
	Camera* CreateCamera(Vec3 Pos, Vec3 LookAt, int FOV, float Aspect, float Near, float Far);

	CameraController* CreateCameraController();

	void SetCurrentCameraController(CameraController* pCon);
	void SetCurrentCameraController(int index);
}

#endif // !CAMERA_MANAGER_H