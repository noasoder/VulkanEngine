#include "Managers/InputManager.h"
#include "Managers/WindowManager.h"

#include "Engine.h"
#include "Utility/Types.h"

void InputManager::Init()
{
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(WindowManager::GetWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    glfwSetInputMode(WindowManager::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void InputManager::Destroy()
{

}

int InputManager::GetKey(int key)
{
    return glfwGetKey(WindowManager::GetWindow(), key);
}

const char* InputManager::GetKeyName(int key, int scancode)
{
    return glfwGetKeyName(key, scancode);
}

glm::vec2 InputManager::GetMousePosition()
{
    double xpos, ypos;
    glfwGetCursorPos(WindowManager::GetWindow(), &xpos, &ypos);

    return glm::vec2(xpos, ypos);
}