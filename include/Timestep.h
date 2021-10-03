#pragma once

#include "Utility/Singleton.h"
#include "Utility/Maths.h"

class Timestep : public Singleton<Timestep>
{
public:
    Timestep(float time = 0.0f)
    : m_Timestep(time)
    {

    };

    float GetSeconds() const { return m_Timestep; };
    float GetMilliseconds() const { return m_Timestep * 1000.0f; };

    float GetDeltaTime() { return GetSeconds(); };
    uint32_t GetFPS() const { return 1.0f / m_Timestep; };

    void SetTimestep(float time) { m_Timestep = time; };
    void SetTime(double time) { m_Time = time; };

    void UpdateTimestep() {
        std::chrono::high_resolution_clock m_clock;
        double nanoSec = std::chrono::duration_cast<std::chrono::nanoseconds>(m_clock.now().time_since_epoch()).count();

        double time = nanoSec / BILLION;
        SetTimestep(time - m_LastFrameTime);
        SetTime(time);

        m_LastFrameTime = time;
    }
private:
    double m_Time;
    double m_LastFrameTime;
    float m_Timestep;
};
