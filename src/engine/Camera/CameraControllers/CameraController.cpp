#include "Camera/CameraControllers/CameraController.h"

#include "Vulkan.h"
#include "Utility/Types.h"
#include "Application.h"
#include "Managers/InputManager.h"
#include "Camera/Camera.h"
#include "Managers/CameraManager.h"
#include "Engine.h"

CameraController::CameraController(Engine* pEngine)
: m_pInputManager(pEngine->m_pInputManager)
, m_pCameraManager(pEngine->m_pCameraManager)
, m_currMoveSpeed(0)
, m_moveSpeedSlow(3)
, m_moveSpeed(10)
, m_moveSpeedFast(20)
, m_lastMousePos(0, 0)
{
    Camera* currCamera = m_pCameraManager->GetCurrentCamera();
}

CameraController::~CameraController()
{

}

void CameraController::Update(float DeltaTime)
{
    glm::vec3 moveLUA = glm::vec3();
    glm::vec3 moveRDB = glm::vec3();

    if (m_pInputManager->GetKey(GLFW_KEY_W))
        moveLUA = moveLUA + glm::vec3(0, 1, 0);
    if (m_pInputManager->GetKey(GLFW_KEY_A))
        moveLUA = moveLUA + glm::vec3(-1, 0, 0);
    if (m_pInputManager->GetKey(GLFW_KEY_S))
        moveRDB = moveRDB + glm::vec3(0, -1, 0);
    if (m_pInputManager->GetKey(GLFW_KEY_D))
        moveRDB = moveRDB + glm::vec3(1, 0, 0);
    if (m_pInputManager->GetKey(GLFW_KEY_E))
        moveLUA = moveLUA + glm::vec3(0, 0, 1);
    if (m_pInputManager->GetKey(GLFW_KEY_Q))
        moveRDB = moveRDB + glm::vec3(0, 0, -1);

    if (m_pInputManager->GetKey(GLFW_KEY_LEFT_SHIFT))
        m_currMoveSpeed = m_moveSpeedFast;
    else if (m_pInputManager->GetKey(GLFW_KEY_LEFT_CONTROL))
        m_currMoveSpeed = m_moveSpeedSlow;
    else
        m_currMoveSpeed = m_moveSpeed;

    glm::vec3 rot = glm::vec3();

    glm::vec3 movePos = (moveLUA + moveRDB) * m_currMoveSpeed * DeltaTime;

    glm::vec2 mousePos = m_pInputManager->GetMousePosition();
    glm::vec2 mouseMove = (m_lastMousePos - mousePos) * 0.1f;
    m_lastMousePos = mousePos;
    rot = glm::vec3(mouseMove.y, 0, mouseMove.x);
    glm::vec3 moveLength = abs(rot);

    Camera* currCamera = m_pCameraManager->GetCurrentCamera();
    currCamera->RotateCam(rot, moveLength);
    currCamera->TranslateLocal(movePos);
}