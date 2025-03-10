#pragma once

#include <iterator>

#include <boost/stl_interfaces/iterator_interface.hpp>

#include <utils/CellIndex.hpp>

namespace ut::detail {

template <typename Derived>
using IndexIteratorBase = boost::stl_interfaces::proxy_iterator_interface<
        Derived,
        std::forward_iterator_tag,
        NormalizedIndex
    >;

} // namespace ut::detail

namespace ut {

class IndexIterator :
    public detail::IndexIteratorBase<IndexIterator>
{
public:
    using Base = detail::IndexIteratorBase<IndexIterator>;

    constexpr IndexIterator() noexcept = default;
    constexpr IndexIterator(size_t positionInContainer, size_t cols) noexcept
        : positionInContainer{positionInContainer}
        , cols{cols}
    {}

    constexpr NormalizedIndex operator*() const noexcept {
        return detail::fromContainerIndex(cols, positionInContainer);
    }

    constexpr IndexIterator& operator++() noexcept {
        ++positionInContainer;
        return *this;
    }
    using Base::operator++;

    friend constexpr bool operator==(const IndexIterator& lhs,
                                     const IndexIterator& rhs) noexcept {
        return lhs.positionInContainer == rhs.positionInContainer;
    }
private:
    size_t positionInContainer{0u};
    size_t cols{0u};
};

static_assert(std::forward_iterator<IndexIterator>);

} // namespace ut
