#pragma once

#include <ranges>

#include <utils/CellIndex.hpp>
#include <utils/IndexIterator.hpp>

namespace ut {

class IndexRange : public std::ranges::view_interface<IndexRange> {
public:
    using Base = std::ranges::view_interface<IndexRange>;

    constexpr
    explicit IndexRange(NormalizedIndex size) noexcept
        : size{size}
    {}

    constexpr
    IndexIterator begin() const noexcept {
        return {0, size.col};
    }

    constexpr
    IndexIterator end() const noexcept {
        return {
            size.row * size.col,
            size.col
        };
    }
private:
    NormalizedIndex size;
};

} // namespace ut
