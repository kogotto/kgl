#pragma once

class Field {
    Cells neigbours(CellIndex);
};
class Cell;
class Cells;

Cells field.neighbours(CellIndex);
Cell rule(Cells neighbours);
Field nextGeneration(Field);

