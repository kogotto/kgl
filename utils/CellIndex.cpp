#include <utils/CellIndex.hpp>

namespace {

size_t normalize(size_t modulo, int32_t raw) {
    while (raw < 0) {
        raw += static_cast<int32_t>(modulo);
    }
    return static_cast<size_t>(raw) % modulo;
}

} // namespace

namespace ut {

NormalizedIndex normalize(NormalizedIndex modulo, CellIndex index) {
    return {
        ::normalize(modulo.row, index.getRawRow()),
        ::normalize(modulo.col, index.getRawCol())
    };
}

} // namespace ut
