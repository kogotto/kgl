#include "field_view.h"

#include <cassert>

#include <field.h>

FieldView::FieldView(const Field& fieldModel, Storage& storage) {
    const auto [fieldRows, fieldCols] = fieldModel.getNormalizedSize();
    const auto storageSize = storage.size();

    assert(4 * fieldRows * fieldCols == storageSize);

    cells.reserve(storageSize);
    for (size_t row = 0; row < fieldRows; ++row) {
        for (size_t col = 0; col < fieldCols; ++col) {
            cells.emplace_back(
                fieldModel.cell(Field::NormalizedIndex{row, col}),
                storage[4 * (row * fieldRows + col)]
            );
        }
    }
}

void FieldView::update() {
    for (auto&& cell : cells) {
        cell.update();
    }
}
