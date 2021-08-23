#include "InputManager.h"

#include "Application.h"
#include "Utility/Types.h"

InputManager::InputManager(Application* pApplication)
: m_pApplication(pApplication)
{

}

InputManager::~InputManager()
{

}

int InputManager::GetKey(int key)
{
    return glfwGetKey(m_pApplication->m_pWindow, key);
}

const char* InputManager::GetKeyName(int key, int scancode)
{
    return glfwGetKeyName(key, scancode);
}

Vec2 InputManager::GetMousePosition()
{
    double xpos, ypos;
    glfwGetCursorPos(m_pApplication->m_pWindow, &xpos, &ypos);

    return Vec2(xpos, ypos);
}