#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdlib>

namespace ut {

using signed_index_t = int32_t;
using normal_index_t = size_t;

struct RowIndex {
    signed_index_t row;

    constexpr RowIndex& operator+=(const RowIndex& rhs) {
        row += rhs.row;
        return *this;
    }
};

struct ColIndex {
    signed_index_t col;

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
    normal_index_t row;
    normal_index_t col;

    friend
    bool operator==(const NormalizedIndex& lhs, const NormalizedIndex& rhs) = default;
};

NormalizedIndex normalize(NormalizedIndex modulo, CellIndex index);

} // namespace ut

namespace ut::detail {

constexpr
size_t toContainerIndex(normal_index_t colsCount, NormalizedIndex index) noexcept {
    return index.row * colsCount + index.col;
}

constexpr
NormalizedIndex fromContainerIndex(normal_index_t colsCount, size_t containerIndex) noexcept {
    const auto div = std::div(containerIndex, static_cast<signed_index_t>(colsCount));
    return {
        static_cast<normal_index_t>(div.quot),
        static_cast<normal_index_t>(div.rem)
    };
}

} // namespace ut::details
