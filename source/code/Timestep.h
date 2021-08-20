#pragma once

class Timestep
{
public:
    Timestep(float time = 0.0f)
    : m_Time(time)
    {

    };

    float GetSeconds() const { return m_Time; };
    float GetMilliseconds() const { return m_Time * 1000.0f; };

    float GetDeltaTime() { return GetSeconds(); };
    uint32_t GetFPS() const { return 1.0f / m_Time; };

    void SetTimestep(float time) { m_Time = time; };
private:

    float m_Time;
};
