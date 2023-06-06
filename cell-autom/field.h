#pragma once

#include <vector>

#include <cell.h>
#include <cells.h>
#include <cellindex.h>

class Field {
public:
    Field(size_t rowsCount, size_t colsCount)
        : rows(rowsCount, Row(colsCount))
    {}

    Cells neighbours(CellIndex index);

private:
    using Row = std::vector<Cell>;
    using Rows = std::vector<Row>;
    Rows rows;
};

Cell rule(Cells neighbours);

