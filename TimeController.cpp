#include "TimeController.hpp"

TimeController::TimeController(Duration period, Callback callback)
    : time_{period}
    , callback_{std::move(callback)}
{}

void TimeController::tick() {
    if (!pause && time_.hasCome()) {
        callback_();
    }
}

void TimeController::togglePause() {
    pause = !pause;
}
