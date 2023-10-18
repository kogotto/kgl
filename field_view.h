#pragma once

#include "storage.h"
#include "cell_view.h"

#include <field_model.h>

class Field;

class FieldView {
public:
    FieldView(ut::NormalizedIndex size, Storage& storage);

    void update(const ca::FieldModel& field);
private:
    ut::Field<CellView> cells;
};
