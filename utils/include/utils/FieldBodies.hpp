#pragma once

#include <utils/Field.hpp>

namespace ut {

template <std::default_initializable T>
inline Field<T>::Field(size_type rowsCount, size_type colsCount)
    : Field(NormalizedIndex{rowsCount, colsCount}) {}

template <std::default_initializable T>
inline Field<T>::Field(NormalizedIndex size)
    : size{size}
    , field(size.row * size.col) {}

template <std::default_initializable T>
template <typename U>
Field<U> Field<T>::createWithSameSize() const {
    return {getSize()};
}

template <std::default_initializable T>
inline auto Field<T>::cell(NormalizedIndex index) const -> const_reference {
    return field[detail::toContainerIndex(getColsCount(), index)];
}

template <std::default_initializable T>
inline auto Field<T>::cell(NormalizedIndex index) -> reference {
    return field[detail::toContainerIndex(getColsCount(), index)];
}

template <std::default_initializable T>
inline auto Field<T>::cell(CellIndex index) const -> const_reference {
    return cell(normalize(getSize(), index));
}

template <std::default_initializable T>
inline auto Field<T>::cell(CellIndex index) -> reference {
    return cell(normalize(getSize(), index));
}

template <std::default_initializable T>
inline IndexRange Field<T>::indexRange() const {
    return IndexRange{getSize()};
}

} // namespace ut
