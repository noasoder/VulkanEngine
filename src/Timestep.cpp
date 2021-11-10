
#include "Timestep.h"

namespace Time
{
    double m_time = 0.0;
    double m_lastFrameTime;
    double m_deltaTime;

    double GetSeconds() { return m_deltaTime; };
    double GetMilliseconds() { return m_deltaTime * 1000.0f; };

    double GetDeltaTime() { return GetSeconds(); };
    uint32_t GetFPS() { return (uint32_t)(1.0f / m_deltaTime); };

    void SetTimestep(double time) { m_deltaTime = time; };
    void SetTime(double time) { m_time = time; };

    void UpdateTimestep()
    {
        std::chrono::high_resolution_clock m_clock;
        double nanoSec = std::chrono::duration_cast<std::chrono::nanoseconds>(m_clock.now().time_since_epoch()).count();

        double time = nanoSec / BILLION;
        SetTimestep(time - m_lastFrameTime);
        SetTime(time);

        m_lastFrameTime = time;
    }
}
