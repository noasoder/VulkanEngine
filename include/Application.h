#pragma once 

#include "Vulkan.h"

#include <chrono>
#include <cstdint>

#include "Timestep.h"
#include "Utility/Maths.h"

class CameraController;
class Model;
class Engine;

class Application
{
public:
    Application();
    ~Application();
    void Run();
    void CloseApplication();

private:
    bool m_Running;
    double m_LastFrameTime;

    Engine* m_pEngine;
};