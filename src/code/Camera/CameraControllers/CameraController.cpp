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
, m_currMoveSpeed(0)
, m_moveSpeedSlow(3)
, m_moveSpeed(5)
, m_moveSpeedFast(7)
, m_lastMousePos(0, 0)
{
    Vec3 pos = Vec3(0, -2, 0);

    Camera* currCamera = m_pCameraManager->GetCurrentCamera();
    //if (currCamera)
    //    currCamera->SetWorldPosition(pos);
    //else
    //    printf("no current camera");
}

CameraController::~CameraController()
{

}

void CameraController::Update(float DeltaTime)
{
    Vec3 moveLUA = Vec3();
    Vec3 moveRDB = Vec3();

    if (m_pInputManager->GetKey(GLFW_KEY_W))
        moveLUA = moveLUA + Vec3(0, 1, 0);
    if (m_pInputManager->GetKey(GLFW_KEY_A))
        moveLUA = moveLUA + Vec3(-1, 0, 0);
    if (m_pInputManager->GetKey(GLFW_KEY_S))
        moveRDB = moveRDB + Vec3(0, -1, 0);
    if (m_pInputManager->GetKey(GLFW_KEY_D))
        moveRDB = moveRDB + Vec3(1, 0, 0);
    if (m_pInputManager->GetKey(GLFW_KEY_E))
        moveLUA = moveLUA + Vec3(0, 0, 1);
    if (m_pInputManager->GetKey(GLFW_KEY_Q))
        moveRDB = moveRDB + Vec3(0, 0, -1);
    if (m_pInputManager->GetKey(GLFW_KEY_LEFT_SHIFT))
        m_currMoveSpeed = m_moveSpeedFast;
    else if (m_pInputManager->GetKey(GLFW_KEY_LEFT_CONTROL))
        m_currMoveSpeed = m_moveSpeedSlow;
    else
        m_currMoveSpeed = m_moveSpeed;

    Vec3 rot = Vec3();

    //if (m_pInputManager->GetKey(GLFW_KEY_UP))
    //    rot = rot + Vec3(1, 0, 0);
    //if (m_pInputManager->GetKey(GLFW_KEY_DOWN))
    //    rot = rot + Vec3(-1, 0, 0);
    //if (m_pInputManager->GetKey(GLFW_KEY_RIGHT))
    //    rot = rot + Vec3(0, 1, 0);
    //if (m_pInputManager->GetKey(GLFW_KEY_LEFT))
    //    rot = rot + Vec3(0, -1, 0);

    rot = rot * 1.0f * DeltaTime;

    //Rotor3 rotor = Rotor3(10, 0, 1, 0);

    //Vec3 rot = rotor.rotate(Vec3(PI, 0, 0));
    //

    Vec3 movePos = (moveLUA + moveRDB) * m_currMoveSpeed * DeltaTime;

    Vec2 mousePos = m_pInputManager->GetMousePosition();
    Vec2 mouse = (mousePos - m_lastMousePos) * 0.002f;
    m_lastMousePos = mousePos;

    
    Camera* currCamera = m_pCameraManager->GetCurrentCamera();

    if (m_pInputManager->GetKey(GLFW_KEY_UP))
        currCamera->Rotate(1, 0, 0, 1.0f * DeltaTime);
    if (m_pInputManager->GetKey(GLFW_KEY_DOWN))
        currCamera->Rotate(1, 0, 0, -1.0f * DeltaTime);
    if (m_pInputManager->GetKey(GLFW_KEY_RIGHT))
        currCamera->Rotate(0, 0, 1, 20.0f * DeltaTime);
    if (m_pInputManager->GetKey(GLFW_KEY_LEFT))
        currCamera->Rotate(0, 0, 1, -20.0f * DeltaTime);
    //currCamera->RotateXZ(Vec2(mouse.y, mouse.x));
    //currCamera->Translate(movePos);
    //currCamera->Rotate(rot);



    //Vec3 at = currCamera->m_rotor.rotate(Vec3(0, 1, 0));
    //printf("At: %f, %f, %f\n", at.x, at.y, at.z);

    //printf("\nL: %f, %f, %f, %f\n U: %f, %f, %f, %f\n A: %f, %f, %f, %f\n P: %f, %f, %f, %f\n",
    //    currCamera->m0.x, currCamera->m0.y, currCamera->m0.z, currCamera->m0.w,
    //    currCamera->m1.x, currCamera->m1.y, currCamera->m1.z, currCamera->m1.w,
    //    currCamera->m2.x, currCamera->m2.y, currCamera->m2.z, currCamera->m2.w,
    //    currCamera->m3.x, currCamera->m3.y, currCamera->m3.z, currCamera->m3.w);
}