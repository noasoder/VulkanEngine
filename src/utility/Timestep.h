#ifndef TIME_H
#define TIME_H

#include "Maths.h"
#include <chrono>

namespace Time
{
    double GetSeconds();
    double GetMilliseconds();

    double GetDeltaTime();
    uint32_t GetFPS();

    void SetTimestep(double time);
    void SetTime(double time);

    void UpdateTimestep();
};

#endif // !TIME_H