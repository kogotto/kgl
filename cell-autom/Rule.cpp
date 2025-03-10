#include <cell-autom/Rule.hpp>

#include <cassert>
#include <algorithm>

namespace ca {
namespace {

size_t aliveCount(Cells neighbours) {
    return std::count(
            std::begin(neighbours),
            std::end(neighbours),
            Cell::Alive
    );
}

} // namespace
} // namespace ca

namespace ca {

Cell rule(Cell cell, Cells neighbours) {
    auto aliveAround = aliveCount(neighbours);

    switch (cell) {
        case Cell::Died:
            return aliveAround == 3
                ? Cell::Alive
                : Cell::Died;
        case Cell::Alive:
            return (aliveAround == 2) || (aliveAround == 3)
                ? Cell::Alive
                : Cell::Died;
        default:
            assert(false && "Unknown Cell::<enumerator>");
    };
}

} // namespace ca
