#include "FieldView.hpp"

#include <cassert>

#include <cell-autom/FieldModel.hpp>

#include <utils/Field.hpp>

#include "PrepareViews.hpp"

namespace {

inline float step(float start, float finish, size_t count) {
    return (finish - start) / count;
}

inline float ratio(size_t index, size_t count) {
    return static_cast<float>(index) / count;
}

inline float linearInterpolation(float start, float finish, float ratio) {
    return start + (finish - start) * ratio;
}

} // namespace

FieldView::FieldView(ut::NormalizedIndex size, ut::Rectf rect)
    : cells{size} {
    const auto [rows, cols] = size;

    const float stepX = step(rect.left, rect.right, cols);
    const float stepY = step(rect.top, rect.bottom, rows);

    for (const auto index : ut::IndexRange{size}) {
        auto&& targetCell = cells.cell(index);

        const auto left =
            linearInterpolation(rect.left, rect.right, ratio(index.col, cols));

        const auto top =
            linearInterpolation(rect.top, rect.bottom, ratio(index.row, rows));

        ut::Rect rect{left, top, left + stepX, top + stepY};

        targetCell.setPosition(rect);
    }
}

void FieldView::update(const ca::FieldModel& field, GraphicsData& data) const {
    assert(field.getSize() == cells.getSize());

    data.v.storage().clear();
    data.i.storage().clear();

    for (auto index : field.indexRange()) {
        cells.cell(index).update(field.cell(index), getOrigin(), data);
    }
}

void FieldView::setOrigin(ut::Pointf origin) { origin_ = origin; }

ut::Pointf FieldView::getOrigin() const { return origin_; }
