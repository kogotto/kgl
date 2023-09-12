#pragma once

#include <chrono>

class Timer {
public:
    using Clock = std::chrono::steady_clock;
    using Timepoint = Clock::time_point;
    using Duration = Timepoint::duration;

    Timer(Duration duration);

    bool hasCome() const;
private:
    mutable Timepoint lastTick;
    Duration duration;
};
