#include <string>
#include <functional>

#include <utils/point.h>

namespace ui::detail {

inline auto nullCallback = [] (ut::Pointf) {};

} // namespace ui::detail

namespace ui {

class MouseListener {
public:
    using Callback = std::function<void(ut::Pointf)>;

    enum class State {
        Idle,
        Drag
    };

    MouseListener() = default;

    MouseListener(const MouseListener&) = delete;
    MouseListener(MouseListener&&) = default;

    MouseListener& operator=(const MouseListener&) = delete;
    MouseListener& operator=(MouseListener&&) = default;

    void setStartDragCallback(Callback callback) {
        startDragCallback_ = std::move(callback);
    }
    void setDragCallback(Callback callback) {
        dragCallback_ = std::move(callback);
    }

    void setPosition(ut::Pointf position);
    void setLeftButtonPressed(bool pressed);
    void setRightButtonPressed(bool pressed);

    std::string makeCaption() const;
private:
    ut::Pointf position_{};

    bool leftButtonPressed_{false};
    bool rightButtonPressed_{false};

    State state_{State::Idle};

    Callback startDragCallback_{detail::nullCallback};
    Callback dragCallback_{detail::nullCallback};
};

}
