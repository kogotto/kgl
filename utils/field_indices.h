#pragma once

#include <cstddef>
#include <cstdint>

namespace ut {

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

struct CellIndex {
    constexpr CellIndex(RowIndex rowIndex, ColIndex colIndex) noexcept
        : row{rowIndex}
        , col{colIndex}
    {}

    constexpr auto getRawRow() const {
        return row.row;
    }

    constexpr auto getRawCol() const {
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

    RowIndex row;
    ColIndex col;
};

struct NormalizedIndex {
    size_t row;
    size_t col;
};

NormalizedIndex normalize(NormalizedIndex modulo, CellIndex index);

} // namespace ut
