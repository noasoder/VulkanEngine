#pragma once

#include	"Vulkan.h"

class Vec2;
class Application;

static class InputManager
{
public:
	InputManager(Application* pApplication);
	~InputManager();

	int GetKey(int key);
	const char* GetKeyName(int key, int scancode = 0);

	Vec2 GetMousePosition();
private:
	Application* m_pApplication;
};