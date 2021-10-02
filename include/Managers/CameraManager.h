#pragma once

#include <vector>
#include "Utility/Types.h"

class Engine;
class Camera;
class CameraController;

class CameraManager
{
public:
	CameraManager(Engine* pEngine);
	~CameraManager();

	void Update(float DeltaTime);

	Camera* GetCurrentCamera() { return m_cameras.at(m_currentCamera); };
	Camera* CreateCamera(Vec3 Pos, Vec3 LookAt, int FOV, float Aspect, float Near, float Far);


	CameraController* CreateCameraController(Engine* pEngine);

	void SetCurrentCameraController(CameraController* pCon);
	void SetCurrentCameraController(int index);

private:
	Engine* m_pEngine;

	std::vector<Camera*> m_cameras;
	std::vector<CameraController*> m_cameraControllers;

	int m_currentCamera;
	int m_currentCameraController;
};

