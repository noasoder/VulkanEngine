#pragma once

class Application;
class InputManager;
class VulkanManager;
class CameraManager;

#include "Utility/Types.h"

class CameraController
{
public:
	CameraController(Application* app);
	~CameraController();

	void Update(float DeltaTime);

private :
	InputManager* m_pInputManager;
	CameraManager* m_pCameraManager;

	float m_currMoveSpeed;
	float m_moveSpeed;
	float m_moveSpeedFast;
	float m_moveSpeedSlow;
	Vec2 m_lastMousePos;
};