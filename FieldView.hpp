#pragma once

#include <utils/Field.hpp>
#include <utils/Point.hpp>

#include <cell-autom/FieldModel.hpp>

#include "CellView.hpp"

class GraphicsData;

class FieldView {
  public:
    FieldView(ut::NormalizedIndex size, ut::Rectf rect);

    void update(const ca::FieldModel& field, GraphicsData& data) const;

    void setOrigin(ut::Pointf origin);
    ut::Pointf getOrigin() const;

    std::optional<ut::NormalizedIndex> getIndexByMousePos(ut::Pointf pos) const;

  private:
    ut::Field<CellView> cells;
    ut::Pointf origin_;
};
