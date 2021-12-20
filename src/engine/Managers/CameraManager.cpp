#include "Managers/CameraManager.h"

#include "Types.h"
#include "Camera/Camera.h"
#include "Camera/CameraControllers/CameraController.h"

namespace CameraManager
{
	std::vector<Camera*> m_cameras;
	std::vector<CameraController*> m_cameraControllers;

	int m_currentCamera;
	int m_currentCameraController;

	void Init()
	{
		m_currentCamera = -1;
		m_currentCameraController = -1;
	};

	void Destroy()
	{
		m_cameras.clear();
		m_cameraControllers.clear();
	};

	void Update(float DeltaTime)
	{
		if (m_currentCameraController != -1)
		{
			m_cameraControllers[m_currentCameraController]->Update(DeltaTime);
		}
	};

	Camera* GetCurrentCamera() { return m_cameras.at(m_currentCamera); };

	Camera* CreateCamera(Vec3 Pos, Vec3 LookAt, int FOV, float Aspect, float Near, float Far)
	{
		Camera* newCamera = new Camera(Pos, LookAt, FOV, Aspect, Near, Far);

		if (m_cameras.empty()) {
			m_currentCamera = 0;
		}

		m_cameras.push_back(newCamera);

		return newCamera;
	};

	CameraController* CreateCameraController()
	{
		m_cameraControllers.push_back(new CameraController());
		return m_cameraControllers[m_cameraControllers.size() - 1];
	};

	void SetCurrentCameraController(CameraController* pCon)
	{
		for (int i = 0; i < m_cameraControllers.size(); i++)
		{
			if (m_cameraControllers[i] == pCon)
			{
				m_currentCameraController = i;
			}
		}
	};

	void SetCurrentCameraController(int index)
	{
		m_currentCameraController = index;
	};
}