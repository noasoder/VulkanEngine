#pragma once

#include <vector>
#include "Utility/Types.h"
#include "Utility/Singleton.h"

class Engine;
class Camera;
class CameraController;

class CameraManager : public Singleton<CameraManager>
{
public:
	CameraManager();
	~CameraManager();

	void Update(float DeltaTime);

	Camera* GetCurrentCamera() { return m_cameras.at(m_currentCamera); };
	Camera* CreateCamera(Vec3 Pos, Vec3 LookAt, int FOV, float Aspect, float Near, float Far);


	CameraController* CreateCameraController();

	void SetCurrentCameraController(CameraController* pCon);
	void SetCurrentCameraController(int index);

private:

	std::vector<Camera*> m_cameras;
	std::vector<CameraController*> m_cameraControllers;

	int m_currentCamera;
	int m_currentCameraController;
};

