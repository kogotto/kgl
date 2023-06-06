#include <field.h>

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

constexpr std::array<CellIndex, 8u> neighbourIndices {
    topLeft,      top,     topRight,
    left,                     right,
    bottomLeft, bottom, bottomRight,
};

} // namespace

Cells Field::neighbours(CellIndex index) {
    return {};
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
    };
}
