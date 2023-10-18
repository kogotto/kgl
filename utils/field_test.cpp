#include <gtest/gtest.h>

#include <utils/field.h>

TEST(FieldTest, Some) {
    ut::Field<int> field(2, 3);

    ASSERT_EQ(2, field.getRowsCount());
    ASSERT_EQ(3, field.getColsCount());

    ASSERT_EQ(field.cell(ut::CellIndex{ut::RowIndex{0}, ut::ColIndex{0}}), 0);
}

TEST(FieldTest, createWithSameSize) {
    const ut::Field<int> origin(128, 256);
    const auto sameSizeField = origin.createWithSameSize<double>();

    ASSERT_EQ(origin.getSize(), sameSizeField.getSize());
}
