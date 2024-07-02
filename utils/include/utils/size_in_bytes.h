#pragma once

#include <vector>

namespace ut {

template <typename T>
inline std::ptrdiff_t sizeInBytes(const std::vector<T>& vec) {
    return vec.size() * sizeof(T);
}

} // namespace glw::detail
