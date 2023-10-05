#pragma once

#include "field.h"

namespace ut::details {

inline size_t toContainerIndex(size_t colsCount, NormalizedIndex index) {
    return index.row * colsCount + index.col;
}

} // namespace ut::details

namespace ut {

template <typename T>
inline Field<T>::Field(size_type rowsCount, size_type colsCount)
    : Field(NormalizedIndex{rowsCount, colsCount})
{}

template <typename T>
inline Field<T>::Field(NormalizedIndex size)
    : size{size}
    , field(size.row * size.col)
{}

template <typename T>
inline auto Field<T>::cell(NormalizedIndex index) const -> const_reference {
    return field[details::toContainerIndex(getColsCount(), index)];
}

template <typename T>
inline auto Field<T>::cell(NormalizedIndex index) -> reference {
    return field[details::toContainerIndex(getColsCount(), index)];
}

template <typename T>
inline auto Field<T>::cell(CellIndex index) const -> const_reference {
    return cell(normalize(getSize(), index));
}

template <typename T>
inline auto Field<T>::cell(CellIndex index) -> reference {
    return cell(normalize(getSize(), index));
}

} // namespace ut
