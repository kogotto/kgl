#pragma once

#include <cstddef>
#include <cstdint>

struct RowIndex {
    int32_t row;

    constexpr RowIndex& operator+=(const RowIndex& rhs) {
        row += rhs.row;
        return *this;
    }
};

struct ColIndex {
    int32_t col;

    constexpr ColIndex& operator+=(const ColIndex& rhs) {
        col += rhs.col;
        return *this;
    }
};

class CellIndex {
public:
    constexpr CellIndex(RowIndex rowIndex, ColIndex colIndex) noexcept
        : row{rowIndex}
        , col{colIndex}
    {}

    constexpr auto getRow() const {
        return row.row;
    }

    constexpr auto getCol() const {
        return col.col;
    }

    constexpr CellIndex& operator+=(const CellIndex& rhs) {
        row += rhs.row;
        col += rhs.col;
        return *this;
    }

    friend constexpr CellIndex operator+(const CellIndex& lhs, const CellIndex& rhs) {
        auto temp{lhs};
        return temp += rhs;
    }

private:
    RowIndex row;
    ColIndex col;
};
