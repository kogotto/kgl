#include "field_model.h"

#include <cassert>

#include "cells.h"
#include "rule.h"

namespace ca {
namespace {

constexpr ut::RowIndex rowBefore{-1};
constexpr ut::RowIndex sameRow{0};
constexpr ut::RowIndex rowAfter{1};

constexpr ut::ColIndex colBefore{-1};
constexpr ut::ColIndex sameCol{0};
constexpr ut::ColIndex colAfter{1};

constexpr CellIndex top{rowBefore, sameCol};
constexpr CellIndex left{sameRow, colBefore};
constexpr CellIndex bottom{rowAfter, sameCol};
constexpr CellIndex right{sameRow, colAfter};

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
    Cells result;
    for (size_t i = 0; i < input.size(); ++i) {
        result[i] = func(input[i]);
    }
    return result;
}

Cells neighbours(const FieldModel& field, CellIndex index) {
    return combine(
            neighbourIndices,
            [&field, index] (CellIndex neighbourIndex) -> Cell {
                return field.cell(index + neighbourIndex);
            });
}

}
} // namespace ca

namespace ca {

void nextGeneration(FieldModel& result, const FieldModel& current) {
    assert(current.getSize() == result.getSize());

    for (const auto index : current.indexRange()) {
        result.cell(index) = rule(current.cell(index),
                                  neighbours(current, CellIndex(index)));
    }
}

void insertGlider(FieldModel& field, CellIndex offset) {
    constexpr std::array<CellIndex, 5> aliveCells = {
        CellIndex{RowIndex{0}, ColIndex{1}},
        CellIndex{RowIndex{1}, ColIndex{2}},
        CellIndex{RowIndex{2}, ColIndex{0}},
        CellIndex{RowIndex{2}, ColIndex{1}},
        CellIndex{RowIndex{2}, ColIndex{2}}
    };

    for (const auto index : aliveCells) {
        field.cell(offset + index) = Cell::Alive;
    }
}

void insertStick(FieldModel& field, CellIndex offset) {
    constexpr std::array<CellIndex, 3> aliveCells = {
        CellIndex{RowIndex{0}, ColIndex{0}},
        CellIndex{RowIndex{0}, ColIndex{1}},
        CellIndex{RowIndex{0}, ColIndex{2}},
    };

    for (const auto index : aliveCells) {
        field.cell(offset + index) = Cell::Alive;
    }
}

void insertRPentamino(FieldModel& field, CellIndex offset) {
    constexpr std::array<CellIndex, 5> aliveCells = {
        CellIndex{RowIndex{0}, ColIndex{1}},
        CellIndex{RowIndex{0}, ColIndex{2}},
        CellIndex{RowIndex{1}, ColIndex{0}},
        CellIndex{RowIndex{1}, ColIndex{1}},
        CellIndex{RowIndex{2}, ColIndex{1}},
    };

    for (const auto index : aliveCells) {
        field.cell(offset + index) = Cell::Alive;
    }
}

} // namespace ca
