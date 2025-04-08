#include "FieldViewMouseAdapter.hpp"

#include "FieldView.hpp"

FieldViewMouseAdapter::FieldViewMouseAdapter(FieldView& view)
    : view_(view) {}

void FieldViewMouseAdapter::startDrag(ut::Pointf mousePos) {
    startMousePos_ = mousePos;
    startViewPos_ = view_.getOrigin();
}

void FieldViewMouseAdapter::drag(ut::Pointf mousePos) {
    const auto delta = mousePos - startMousePos_;
    view_.setOrigin(startViewPos_ + delta);
}
