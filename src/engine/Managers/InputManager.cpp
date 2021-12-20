#include "Managers/InputManager.h"
#include "Managers/WindowManager.h"

#include "Engine.h"
#include "Types.h"
#include <list>
#include <vector>

std::vector<int> m_startedPressingKey;
std::vector<int> m_stoppedPressingKey;

void InputManager::Init()
{
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(WindowManager::GetWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    glfwSetInputMode(WindowManager::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetKeyCallback(WindowManager::GetWindow(), KeyCallback);
}

void InputManager::Destroy()
{

}

void InputManager::Update()
{
    m_startedPressingKey.clear();
    m_stoppedPressingKey.clear();
}

bool InputManager::GetKeyDown(int key)
{
    for (int k : m_startedPressingKey)
    {
        if (k == key)
        {
            return true;
        }
    }
    return false;
}

bool InputManager::GetKeyUp(int key)
{
    for (int k : m_startedPressingKey)
    {
        if (k == key)
        {
            return true;
        }
    }
    return false;
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

void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        m_startedPressingKey.push_back(key);
    }
}