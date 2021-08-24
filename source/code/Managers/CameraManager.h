#pragma once

#include <vector>

class Application;
class Camera;
class Vec3;

class CameraManager
{
public:
	CameraManager(Application* pApplication);
	~CameraManager();


	Camera* GetCurrentCamera() { return m_cameras.at(m_currentCamera); };
	Camera* CreateCamera(Vec3 Pos, Vec3 LookAt, int FOV, float Aspect);
private:
	Application* m_pApplication;

	std::vector<Camera*> m_cameras;

	int m_currentCamera = 0;
};

