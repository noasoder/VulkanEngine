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

    void UpdateTimestep() {
        std::chrono::high_resolution_clock m_clock;
        double nanoSec = std::chrono::duration_cast<std::chrono::nanoseconds>(m_clock.now().time_since_epoch()).count();

        double time = nanoSec / BILLION;
        m_timestep.SetTimestep(time - m_LastFrameTime);
        m_timestep.SetTime(time);

        m_LastFrameTime = time;
    }

private:
    bool m_Running;
    double m_LastFrameTime;

    Engine* m_pEngine;

    Timestep m_timestep;
};