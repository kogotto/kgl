#pragma once

#include <vector>

namespace glw {

template <typename VRTX>
class VertexBuffer {
public:
    using vertex_t = VRTX;
    using storage_t = std::vector<vertex_t>;

private:
};

} // namespace glw
