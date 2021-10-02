#pragma once

class Engine;
class InputManager;
class VulkanManager;
class CameraManager;

#include "Utility/Types.h"

class CameraController
{
public:
	CameraController(Engine* pEngine);
	~CameraController();

	void Update(float DeltaTime);

private :
	InputManager* m_pInputManager;
	CameraManager* m_pCameraManager;

	float m_currMoveSpeed;
	float m_moveSpeed;
	float m_moveSpeedFast;
	float m_moveSpeedSlow;
	glm::vec2 m_lastMousePos;
};