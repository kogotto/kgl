#include <string>

namespace ui {

constexpr int winWidth = 1280;
constexpr int winHeight = 960;

class MouseListener {
public:
    MouseListener() = default;

    MouseListener(const MouseListener&) = delete;
    MouseListener(MouseListener&&) = default;

    MouseListener& operator=(const MouseListener&) = delete;
    MouseListener& operator=(MouseListener&&) = default;

    void setPosition(double x, double y);
    void setLeftButtonPressed(bool pressed);
    void setRightButtonPressed(bool pressed);

    std::string makeCaption() const;
private:
    double x_{0.0};
    double y_{0.0};

    bool leftButtonPressed_{false};
    bool rightButtonPressed_{false};
};

}
