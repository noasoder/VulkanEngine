#include "Managers/CameraManager.h"

#include "Utility/Types.h"
#include "Camera/Camera.h"
#include "Application.h"
#include "Camera/CameraControllers/CameraController.h"

CameraManager::CameraManager()
: m_currentCamera(-1)
, m_currentCameraController(-1)
{

}

CameraManager::~CameraManager()
{
	m_cameras.clear();
	m_cameraControllers.clear();
}

void CameraManager::Update(float DeltaTime)
{
	if (m_currentCameraController != -1)
	{
		m_cameraControllers[m_currentCameraController]->Update(DeltaTime);
	}
}

Camera* CameraManager::CreateCamera(Vec3 Pos, Vec3 LookAt, int FOV, float Aspect, float Near, float Far)
{
	Camera* newCamera = new Camera(Pos, LookAt, FOV, Aspect, Near, Far);

	if (m_cameras.empty()) {
		m_currentCamera = 0;
	}

	m_cameras.push_back(newCamera);

	return newCamera;
}

CameraController* CameraManager::CreateCameraController()
{
	m_cameraControllers.push_back(new CameraController());
	return m_cameraControllers[m_cameraControllers.size() - 1];
}

void CameraManager::SetCurrentCameraController(CameraController* pCon)
{
	for (int i = 0; i < m_cameraControllers.size(); i++)
	{
		if (m_cameraControllers[i] == pCon)
		{
			m_currentCameraController = i;
		}
	}
}

void CameraManager::SetCurrentCameraController(int index)
{
	m_currentCameraController = index;
}