#include "field_view.h"

#include <cassert>

#include <utils/field.h>

FieldView::FieldView(ut::NormalizedIndex size, Storage& storage)
    : cells{size}
{
    const auto [rows, cols] = size;
    assert(4 * rows * cols == storage.size());

    for (const auto index : ut::IndexRange{size}) {
        auto&& targetCell = cells.cell(index);
        Vertex* firstVertex = &storage[4 * ut::detail::toContainerIndex(cols, index)];
        targetCell = {
            *firstVertex
        };
        targetCell.setPosition({
            firstVertex[0].position[0],
            firstVertex[0].position[1],
            firstVertex[3].position[0],
            firstVertex[3].position[1],
        });
    }
}

void FieldView::update(const ca::FieldModel& field) {
    assert(field.getSize() == cells.getSize());

    for (auto index : field.indexRange()) {
        cells.cell(index).update(field.cell(index));
    }
}
