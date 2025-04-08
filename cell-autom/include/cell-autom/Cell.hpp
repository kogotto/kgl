#pragma once

namespace ca {

enum class Cell {
    Died,
    Alive,
};

inline void toggle(Cell& cell) {
    switch (cell) {
    case Cell::Died:
        cell = Cell::Alive;
        break;
    case Cell::Alive:
        cell = Cell::Died;
        break;
    default:
        cell = Cell::Died;
    }
}

} // namespace ca
