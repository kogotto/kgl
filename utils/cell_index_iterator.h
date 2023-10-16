#pragma once

#include <boost/stl_interfaces/iterator_interface.hpp>

#include "cell_index.h"

namespace ut::detail {

template <typename Derived>
using CellIndexIteratorBase = boost::stl_interfaces::proxy_iterator_interface<
        Derived,
        std::forward_iterator_tag,
        CellIndex
    >;

} // namespace ut::detail

namespace ut {

class CellIndexIterator :
    public detail::CellIndexIteratorBase<CellIndexIterator>
{
public:
    using Base = detail::CellIndexIteratorBase<CellIndexIterator>;

    constexpr CellIndexIterator() noexcept = default;

    constexpr CellIndex operator*() const noexcept {
        return detail::fromContainerIndex(cols, positionInContainer);
    }

    constexpr CellIndexIterator& operator++() noexcept {
        ++positionInContainer;
        return *this;
    }
    using Base::operator++;

    friend constexpr bool operator==(const CellIndexIterator& lhs,
                                     const CellIndexIterator& rhs) noexcept {
        return lhs.positionInContainer == rhs.positionInContainer;
    }
private:
    size_t positionInContainer{0u};
    size_t cols{0u};
};

static_assert(std::forward_iterator<CellIndexIterator>);

} // namespace ut
