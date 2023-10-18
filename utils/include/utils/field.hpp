#pragma once

#include <utils/field.h>

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
template <typename U>
Field<U> Field<T>::createWithSameSize() const {
    return {getSize()};
}

template <typename T>
inline auto Field<T>::cell(NormalizedIndex index) const -> const_reference {
    return field[detail::toContainerIndex(getColsCount(), index)];
}

template <typename T>
inline auto Field<T>::cell(NormalizedIndex index) -> reference {
    return field[detail::toContainerIndex(getColsCount(), index)];
}

template <typename T>
inline auto Field<T>::cell(CellIndex index) const -> const_reference {
    return cell(normalize(getSize(), index));
}

template <typename T>
inline auto Field<T>::cell(CellIndex index) -> reference {
    return cell(normalize(getSize(), index));
}

template <typename T>
inline IndexRange Field<T>::indexRange() const {
    return IndexRange{getSize()};
}

} // namespace ut
