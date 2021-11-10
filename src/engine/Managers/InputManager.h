#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Vulkan.h"

class Engine;

namespace InputManager
{
	void Init();
	void Destroy();

	int GetKey(int key);
	const char* GetKeyName(int key, int scancode = 0);

	glm::vec2 GetMousePosition();
};

#endif // !INPUT_MANAGER_H