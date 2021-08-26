#pragma once

#include <vector>

class Application;
class Camera;
class CameraController;
class Vec3;

class CameraManager
{
public:
	CameraManager(Application* pApplication);
	~CameraManager();

	void Update(float DeltaTime);

	Camera* GetCurrentCamera() { return m_cameras.at(m_currentCamera); };
	Camera* CreateCamera(Vec3 Pos, Vec3 LookAt, int FOV, float Aspect, float Near, float Far);
	CameraController* CreateCameraController(Application* app);
	void SetCurrentCameraController(CameraController* pCon);
	void SetCurrentCameraController(int index);

private:
	Application* m_pApplication;

	std::vector<Camera*> m_cameras;
	std::vector<CameraController*> m_cameraControllers;

	int m_currentCamera;
	int m_currentCameraController;
};

