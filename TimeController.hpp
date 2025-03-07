#pragma once

#include <functional>

#include <utils/timer.h>

class TimeController {
public:
    using Callback = std::function<void()>;
    using Duration = ut::Timer::Duration;

    TimeController(Duration period, Callback callback);

    void tick();

    void togglePause();
private:
    bool pause{false};
    ut::Timer time_;
    Callback callback_;
};
