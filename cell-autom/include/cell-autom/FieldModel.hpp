#pragma once

#include <utils/Field.hpp>

#include <cell-autom/Cell.hpp>

namespace ca {

using ut::CellIndex;
using ut::ColIndex;
using ut::NormalizedIndex;
using ut::RowIndex;
using FieldModel = ut::Field<Cell>;

void nextGeneration(FieldModel& result, const FieldModel& current);

inline FieldModel nextGeneration(const FieldModel& current) {
    FieldModel result = current.createWithSameSize();

    nextGeneration(result, current);

    return result;
}

void insertGlider(FieldModel& field, CellIndex offset);
void insertStick(FieldModel& field, CellIndex offset);
void insertRPentamino(FieldModel& field, CellIndex offset);

} // namespace ca
