#include <string>

namespace ui {

constexpr int winWidth = 1280;
constexpr int winHeight = 960;

class Mouse {
public:
    Mouse() = default;

    Mouse(const Mouse&) = delete;
    Mouse(Mouse&&) = default;

    Mouse& operator=(const Mouse&) = delete;
    Mouse& operator=(Mouse&&) = default;

    void setPosition(double x, double y);
    std::string makeCaption() const;
private:
    double x_{0.0};
    double y_{0.0};
};

}
