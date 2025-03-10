#pragma once

#include <utils/Point.hpp>

#include "CellView.hpp"

#include <cell-autom/FieldModel.hpp>

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
