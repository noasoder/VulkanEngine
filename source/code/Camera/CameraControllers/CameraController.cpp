#include "CameraController.h"

#include "Vulkan.h"
#include "Utility/Types.h"
#include "Application.h"
#include "Managers/InputManager.h"
#include "Camera/Camera.h"
#include "Managers/CameraManager.h"

CameraController::CameraController(Application* app)
: m_pInputManager(app->m_pInputManager)
, m_pCameraManager(app->m_pCameraManager)
, m_moveSpeedSlow(3)
, m_moveSpeed(5)
, m_moveSpeedFast(7)
, m_lastMousePos(0, 0)
{
    Vec3 pos = Vec3(0, -2, 0);

    Camera* currCamera = m_pCameraManager->GetCurrentCamera();
    if (currCamera)
        currCamera->SetWorldPosition(pos);
    else
        printf("no current camera");
}

CameraController::~CameraController()
{

}

void CameraController::Update(float DeltaTime)
{
    Vec3 moveRAU = Vec3();
    Vec3 moveLDB = Vec3();

    if (m_pInputManager->GetKey(GLFW_KEY_W))
        moveRAU = moveRAU + Vec3(0, 1, 0);
    if (m_pInputManager->GetKey(GLFW_KEY_A))
        moveRAU = moveRAU + Vec3(1, 0, 0);
    if (m_pInputManager->GetKey(GLFW_KEY_S))
        moveLDB = moveLDB + Vec3(0, -1, 0);
    if (m_pInputManager->GetKey(GLFW_KEY_D))
        moveLDB = moveLDB + Vec3(-1, 0, 0);
    if (m_pInputManager->GetKey(GLFW_KEY_E))
        moveRAU = moveRAU + Vec3(0, 0, 1);
    if (m_pInputManager->GetKey(GLFW_KEY_Q))
        moveLDB = moveLDB + Vec3(0, 0, -1);
    if (m_pInputManager->GetKey(GLFW_KEY_LEFT_SHIFT))
        m_currMoveSpeed = m_moveSpeedFast;
    else if (m_pInputManager->GetKey(GLFW_KEY_LEFT_CONTROL))
        m_currMoveSpeed = m_moveSpeedSlow;
    else
        m_currMoveSpeed = m_moveSpeed;

    Vec3 movePos = (moveRAU + moveLDB) * m_currMoveSpeed * DeltaTime;

    Vec2 mousePos = m_pInputManager->GetMousePosition();
    Vec2 mouse = (mousePos - m_lastMousePos) * 0.002f;
    m_lastMousePos = mousePos;


    Camera* currCamera = m_pCameraManager->GetCurrentCamera();
    currCamera->RotateXY(Vec2(mouse.y, mouse.x));
    currCamera->Translate(movePos);
}