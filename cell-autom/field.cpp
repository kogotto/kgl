#include <field.h>

#include <cassert>

#include <rule.h>

namespace {

constexpr CellIndex top{RowIndex{0}, ColIndex{-1}};
constexpr CellIndex left{RowIndex{-1}, ColIndex{0}};
constexpr CellIndex bottom{RowIndex{0}, ColIndex{1}};
constexpr CellIndex right{RowIndex{1}, ColIndex{0}};

constexpr CellIndex topLeft{top + left};
constexpr CellIndex topRight{top + right};
constexpr CellIndex bottomLeft{bottom + left};
constexpr CellIndex bottomRight{bottom + right};

using CellIndices = std::array<CellIndex, 8u>;

constexpr CellIndices neighbourIndices {
    topLeft,      top,     topRight,
    left,                     right,
    bottomLeft, bottom, bottomRight,
};

template <typename Func>
auto combine(CellIndices input, Func func) {
    Cells::Raw result;
    for (size_t i = 0; i < input.size(); ++i) {
        result[i] = func(input[i]);
    }
    return result;
}

using NormalizedIndex = Field::NormalizedIndex;

bool operator==(const NormalizedIndex& lhs, const NormalizedIndex& rhs) {
    return
        lhs.row == rhs.row &&
        lhs.col == rhs.col;
}

size_t normalize(int32_t raw, size_t modulo) {
    while (raw < 0) {
        raw += static_cast<int32_t>(modulo);
    }
    return static_cast<size_t>(raw) % modulo;
}

NormalizedIndex normalize(CellIndex index, NormalizedIndex modulo) {
    return {
        normalize(index.getRow(), modulo.row),
        normalize(index.getCol(), modulo.col)
    };
}

} // namespace

Cells Field::neighbours(CellIndex index) const {
    return combine(
            neighbourIndices,
            [this, index] (const CellIndex& neighbourIndex) -> Cell {
                return cell(index + neighbourIndex);
            });
}

Cell& Field::cell(CellIndex index) {
    const auto normalizedIndex = normalize(index, getNormalizedSize());
    return cell(normalizedIndex);
}

const Cell& Field::cell(CellIndex index) const {
    const auto normalizedIndex = normalize(index, getNormalizedSize());
    return cell(normalizedIndex);
}

Cell Field::cellNextGeneration(CellIndex index) const {
    return rule(cell(index), neighbours(index));
}

Field nextGeneration(const Field& current) {
    const size_t rowCount = current.getRowsCount();
    const size_t colCount = current.getColsCount();
    Field result{rowCount, colCount};

    for (int32_t row = 0; row < rowCount; ++row) {
        for (int32_t col = 0; col < colCount; ++col) {
            const CellIndex index{RowIndex{row}, ColIndex{col}};
            result.cell(index) = rule(current.cell(index), current.neighbours(index));
        }
    }
    return result;
}

namespace {

void nextGenerationSample(const Field& current, Field& result) {
    const auto size = current.getNormalizedSize();
    assert(size == result.getNormalizedSize());

    for (int32_t row = 0; row < size.row; ++row) {
        for (int32_t col = 0; col < size.col; ++col) {
            const CellIndex index{RowIndex{row}, ColIndex{col}};
            result.cell(index) = rule(current.cell(index), current.neighbours(index));
        }
    }
}

} // namespace

void nextGeneration(const Field& current, Field& result) {
    const auto size = current.getNormalizedSize();
    assert(size == result.getNormalizedSize());

    for (auto index : current.indices()) {
        result.cell(index) = current.cellNextGeneration(index);
    }
}
