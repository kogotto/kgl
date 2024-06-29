#include "field_view.h"

#include <cassert>

#include <utils/field.h>

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

FieldView::FieldView(ut::NormalizedIndex size, ut::Rect rect, Storage& storage)
    : cells{size}
{
    const auto [rows, cols] = size;
    assert(4 * rows * cols == storage.size());

    const float stepX = step(rect.left, rect.right, cols);
    const float stepY = step(rect.top, rect.bottom, rows);

    for (const auto index : ut::IndexRange{size}) {
        auto&& targetCell = cells.cell(index);
        Vertex* firstVertex = &storage[4 * ut::detail::toContainerIndex(cols, index)];
        targetCell = {
            *firstVertex
        };

        const auto left = linearInterpolation(
            rect.left,
            rect.right,
            ratio(index.col, cols)
        );

        const auto top = linearInterpolation(
            rect.top,
            rect.bottom,
            ratio(index.row, rows)
        );

        ut::Rect rect{
            left,
            top,
            left + stepX,
            top + stepY
        };

        targetCell.setPosition(rect);
    }
}

void FieldView::update(const ca::FieldModel& field) {
    assert(field.getSize() == cells.getSize());

    for (auto index : field.indexRange()) {
        cells.cell(index).update(field.cell(index));
    }
}
