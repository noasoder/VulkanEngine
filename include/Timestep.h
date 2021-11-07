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

    double GetSeconds() const { return m_Timestep; };
    double GetMilliseconds() const { return m_Timestep * 1000.0f; };

    double GetDeltaTime() { return GetSeconds(); };
    uint32_t GetFPS() const { return (uint32_t)(1.0f / m_Timestep); };

    void SetTimestep(double time) { m_Timestep = time; };
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
    double m_Timestep;
};
