#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdlib>

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

    friend
    bool operator==(const NormalizedIndex& lhs, const NormalizedIndex& rhs) = default;
};

NormalizedIndex normalize(NormalizedIndex modulo, CellIndex index);

} // namespace ut

namespace ut::detail {

inline size_t toContainerIndex(size_t colsCount, NormalizedIndex index) {
    return index.row * colsCount + index.col;
}

inline CellIndex fromContainerIndex(size_t colsCount, size_t containerIndex) {
    const auto div = std::div(containerIndex, (int32_t)colsCount);
    return {
        RowIndex{div.quot},
        ColIndex{div.rem}
    };
}

} // namespace ut::details
