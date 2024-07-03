#pragma once

#include "cell_view.h"

#include <field_model.h>

class Field;
class GraphicsData;

class FieldView {
public:
    FieldView(ut::NormalizedIndex size, ut::Rect rect);

    void update(const ca::FieldModel& field, GraphicsData& data);
private:
    ut::Field<CellView> cells;
};
