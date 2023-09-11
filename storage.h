#pragma once

#include <vector>

struct Vertex {
    float position[2];
    float color[4];
};

using Storage = std::vector<Vertex>;
