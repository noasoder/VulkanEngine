#pragma once

#include	"Vulkan.h"

class Application;

class InputManager
{
public:
	InputManager(Application* pApplication);
	~InputManager();

	int GetKey(int key);
	const char* GetKeyName(int key, int scancode = 0);

	glm::vec2 GetMousePosition();
private:
	Application* m_pApplication;
};