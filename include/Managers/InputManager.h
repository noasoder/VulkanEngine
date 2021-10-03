#pragma once

#include "Vulkan.h"
#include "Utility/Singleton.h"

class Engine;

class InputManager : public Singleton<InputManager>
{
public:

	InputManager();
	~InputManager();

	int GetKey(int key);
	const char* GetKeyName(int key, int scancode = 0);

	glm::vec2 GetMousePosition();
private:
	int m;
};