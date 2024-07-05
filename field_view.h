#pragma once

#include <utils/point.h>

#include "cell_view.h"

#include <field_model.h>

class Field;
class GraphicsData;

class FieldView {
public:
    FieldView(ut::NormalizedIndex size, ut::Rect rect);

    void update(const ca::FieldModel& field, GraphicsData& data);

    void setOrigin(int oX, int oY);
private:
    ut::Point getOrigin() const;

    ut::Field<CellView> cells;
    int oX_{0};
    int oY_{0};
};
