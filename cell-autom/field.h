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

    size_t getRowsCount() const {
        return rows.size();
    }

    size_t getColsCount() const {
        return rows.front().size();
    }

    Cells neighbours(CellIndex index);
    Cell cell(CellIndex index) const;

private:
    using Row = std::vector<Cell>;
    using Rows = std::vector<Row>;
    Rows rows;
};

Cell rule(Cells neighbours);

