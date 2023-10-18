#include "field_view.h"

#include <cassert>

#include <utils/field.h>

FieldView::FieldView(ut::NormalizedIndex size, Storage& storage)
    : cells{size}
{
    const auto [rows, cols] = size;
    assert(4 * rows * cols == storage.size());

    for (const auto index : ut::IndexRange{size}) {
        cells.cell(index) = {
            storage[4 * ut::detail::toContainerIndex(cols, index)]
        };
    }
}

void FieldView::update(const ca::FieldModel& field) {
    assert(field.getSize() == cells.getSize());

    for (auto index : field.indexRange()) {
        cells.cell(index).update(field.cell(index));
    }
}
