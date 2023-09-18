#pragma once

#include "storage.h"
#include "cell_view.h"

class Field;

class FieldView {
public:
    FieldView(const Field& fieldModel, Storage& storage);

    void update();
private:
    std::vector<CellView> cells;
};
