#pragma once

#include	"Vulkan.h"

class Engine;

class InputManager
{
public:
	InputManager(Engine* pEngine, GLFWwindow* window);
	~InputManager();

	int GetKey(int key);
	const char* GetKeyName(int key, int scancode = 0);

	glm::vec2 GetMousePosition();
private:
	Engine* m_pEngine;
	GLFWwindow* m_pWindow;
};