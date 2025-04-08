#pragma once

#include <cell-autom/Cell.hpp>
#include <utils/Rect.hpp>

class Vertex;
class GraphicsData;

class CellView {
  public:
    void setPosition(ut::Rectf newPosition) { position = newPosition; }

    void update(const ca::Cell& cell, ut::Pointf origin,
                GraphicsData& data) const;

    bool contains(ut::Pointf position) const;

  private:
    ut::Rectf position;
};
