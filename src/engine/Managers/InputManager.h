#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Core.h"

class Engine;

namespace InputManager
{
	void Init();
	void Destroy();

	void Update();

	int GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);
	const char* GetKeyName(int key, int scancode = 0);

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	glm::vec2 GetMousePosition();
};

#endif // !INPUT_MANAGER_H