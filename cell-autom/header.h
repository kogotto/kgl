#pragma once

class Field;
class Cell;
class Cells;

Cells field.neighbours(CellIndex);
Cell rule(Cells neighbours);
Field nextGeneration(Field);

