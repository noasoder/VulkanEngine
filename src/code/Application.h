#pragma once 

#include "Vulkan.h"

#include <chrono>
#include <cstdint>

#include "Utility/Maths.h"

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

    Engine* m_pEngine;
};