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

    void setOrigin(float oX, float oY);
private:
    ut::Point getOrigin() const;

    ut::Field<CellView> cells;
    float oX_{0};
    float oY_{0};
};
