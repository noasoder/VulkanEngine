#pragma once

class Timestep
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
private:
    double m_Time;
    float m_Timestep;
};
