#pragma once

#include "Types.h"

class CameraController
{
public:
	CameraController();
	~CameraController();

	void Update(float DeltaTime);

private :
	float m_currMoveSpeed;
	float m_moveSpeed;
	float m_moveSpeedFast;
	float m_moveSpeedSlow;
	glm::vec2 m_lastMousePos;
};