#include <gtest/gtest.h>

#include "field.h"

TEST(Some, Test) {
    ut::Field<int> field(2, 3);

    ASSERT_EQ(2, field.getRowsCount());
    ASSERT_EQ(3, field.getColsCount());

    ASSERT_EQ(field.cell(ut::CellIndex{ut::RowIndex{0}, ut::ColIndex{0}}), 0);
}
