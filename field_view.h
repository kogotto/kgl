#pragma once

#include <utils/point.h>

#include "cell_view.h"

#include <field_model.h>

class Field;
class GraphicsData;

class FieldView {
public:
    FieldView(ut::NormalizedIndex size, ut::Rectf rect);

    void update(const ca::FieldModel& field, GraphicsData& data) const;

    void setOrigin(ut::Pointf origin);
    ut::Pointf getOrigin() const;

private:
    ut::Field<CellView> cells;
    ut::Pointf origin_;
};
