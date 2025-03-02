#include <utils/timer.h>

namespace ut {

Timer::Timer(Duration duration)
    : lastTick(Clock::now())
    , duration(duration)
{}

bool Timer::hasCome() const {
    if (const auto now = Clock::now();
            now > (lastTick + duration)) {
        lastTick = now;
        return true;
    }

    return false;
}

} // namespace ut
