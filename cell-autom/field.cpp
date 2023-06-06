#include <field.h>

#include <cassert>
#include <algorithm>

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

size_t normalize(int32_t raw, size_t modulo) {
    while (raw < 0) {
        raw += static_cast<int32_t>(modulo);
    }
    return static_cast<size_t>(raw) % modulo;
}

} // namespace

Cells Field::neighbours(CellIndex index) {
    return combine(
            neighbourIndices,
            [this, index] (const CellIndex& neighbourIndex) -> Cell {
                return cell(index + neighbourIndex);
            });
}

Cell Field::cell(CellIndex index) const {
    const size_t row = normalize(index.getRow(), getRowsCount());
    const size_t col = normalize(index.getCol(), getColsCount());
    return rows[row][col];
}

size_t aliveCount(Cells neighbours) {
    return std::count(
            std::begin(neighbours),
            std::end(neighbours),
            Cell::Alive
    );

}

Cell rule(Cell cell, Cells neighbours) {
    auto aliveAround = aliveCount(neighbours);

    switch (cell) {
        case Cell::Died:
            return aliveAround == 2
                ? Cell::Alive
                : Cell::Died;
        case Cell::Alive: 
            return (aliveAround == 2) || (aliveAround == 3)
                ? Cell::Alive
                : Cell::Died;
        default:
            assert(false && "Unknown Cell::<enumerator>");
    };
}
