#pragma once

#include <utils/Point.hpp>

class FieldView;

class FieldViewMouseAdapter {
public:
    explicit FieldViewMouseAdapter(FieldView& view);
    void startDrag(ut::Pointf mousePos);
    void drag(ut::Pointf mousePos);
private:
    FieldView& view_;
    ut::Pointf startMousePos_;
    ut::Pointf startViewPos_;
};
