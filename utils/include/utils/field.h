#pragma once

#include <cstddef>
#include <vector>
#include <concepts>

#include <utils/cell_index.h>
#include <utils/index_range.h>

namespace ut {

template <typename T> requires std::default_initializable<T>
class Field {
public:
    using value_type = T;
    using container_type = std::vector<value_type>;
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = const value_type&;

    Field(size_type rowsCount, size_type colsCount);
    Field(NormalizedIndex size);

    Field(const Field& other) = default;
    Field(Field&& other) = default;

    Field& operator=(const Field& other) = default;
    Field& operator=(Field&& other) = default;

    template <typename U = T>
    Field<U> createWithSameSize() const;

    size_type getRowsCount() const { return size.row; }
    size_type getColsCount() const { return size.col; }
    NormalizedIndex getSize() const { return size; }

    const_reference cell(NormalizedIndex index) const;
    reference cell(NormalizedIndex index);

    const_reference cell(CellIndex index) const;
    reference cell(CellIndex index);

    IndexRange indexRange() const;

private:
    NormalizedIndex size;
    container_type field;
};

} // namespace ut

#include "field.hpp"
