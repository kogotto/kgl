#include "rule.h"

#include <cassert>
#include <algorithm>

namespace {

size_t aliveCount(Cells neighbours) {
    return std::count(
            std::begin(neighbours),
            std::end(neighbours),
            Cell::Alive
    );
}

} // namespace

Cell rule(Cell cell, Cells neighbours) {
    auto aliveAround = aliveCount(neighbours);

    switch (cell) {
        case Cell::Died:
            return aliveAround == 2
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
