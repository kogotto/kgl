#pragma once

#include <cstddef>
#include <vector>

#include "field_indices.h"

namespace ut {

template <typename T>
class Field {
public:
    using value_type = T;
    using container_type = std::vector<value_type>;
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = const value_type&;

    Field(size_type rowsCount, size_type colsCount);
    Field(NormalizedIndex size);

    size_type getRowsCount() const { return rowsCount; }
    size_type getColsCount() const { return colsCount; }
    NormalizedIndex getSize() const { return {rowsCount, colsCount}; }

    const_reference cell(NormalizedIndex index) const;
    reference cell(NormalizedIndex index);

    const_reference cell(CellIndex index) const;
    reference cell(CellIndex index);

private:
    size_type rowsCount;
    size_type colsCount;
    container_type field;
};

} // namespace ut

#include "field.hpp"
