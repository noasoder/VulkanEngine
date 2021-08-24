#include "CameraManager.h"

#include "Utility/Types.h"
#include "Camera.h"
#include "Application.h"

CameraManager::CameraManager(Application* pApplication)
: m_pApplication(pApplication)
{

}

CameraManager::~CameraManager()
{
	m_cameras.clear();
}

Camera* CameraManager::CreateCamera(Vec3 Pos, Vec3 LookAt, int FOV, float Aspect)
{
	Camera* newCamera = new Camera(Pos, LookAt, FOV, Aspect, 0.1f, 100.0f);

	if (m_cameras.empty()) {
		m_currentCamera = 0;
	}

	m_cameras.push_back(newCamera);

	return newCamera;
}