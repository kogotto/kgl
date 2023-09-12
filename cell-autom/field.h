#pragma once

#include <vector>

#include <cell.h>
#include <cells.h>
#include <cellindex.h>

class Field {
public:

    struct NormalizedIndex {
        size_t row;
        size_t col;
    };

    struct CellIndexIterator {
        CellIndex operator*() const;
        friend bool operator!=(const CellIndexIterator& lhs, const CellIndexIterator& rhs);
        CellIndexIterator operator++();
    };

    struct Indices {
        CellIndexIterator begin() const;
        CellIndexIterator begin();
        CellIndexIterator end() const;
        CellIndexIterator end();
    };

    Field(size_t rowsCount, size_t colsCount)
        : rows(rowsCount, Row(colsCount, Cell::Died))
    {
        for (size_t row = 0; row < rowsCount; ++row) {
            for (size_t col = 0; col < colsCount; ++col) {
                if ((row + col) % 2 == 0) {
                    rows[row][col] = Cell::Alive;
                }
            }
        }
    }

    size_t getRowsCount() const {
        return rows.size();
    }
    size_t getColsCount() const {
        return rows.front().size();
    }
    NormalizedIndex getNormalizedSize() const {
        return {
            getRowsCount(),
            getColsCount()
        };
    }

    Indices indices() const;
    Indices indices();

    Cells neighbours(CellIndex index) const;

    Cell& cell(NormalizedIndex index) {
        return rows[index.row][index.col];
    }
    const Cell& cell(NormalizedIndex index) const {
        return rows[index.row][index.col];
    }

    Cell& cell(CellIndex index);
    const Cell& cell(CellIndex index) const;

    Cell cellNextGeneration(CellIndex index) const;

private:
    using Row = std::vector<Cell>;
    using Rows = std::vector<Row>;
    Rows rows;
};

Field nextGeneration(const Field& current);
void nextGeneration(const Field& current, Field& result);

