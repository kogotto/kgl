#pragma once

#include <type_traits>

#include <utils/field.h>

#include "cell.h"

namespace ca {

using ut::NormalizedIndex;
using ut::CellIndex;
using FieldModel = ut::Field<Cell>;

void nextGeneration(FieldModel& result, const FieldModel& current);

} // namespace ca
