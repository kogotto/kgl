#pragma once

#include <glw/VertexArray.hpp>
#include <glw/VertexBuffer.hpp>
#include <glw/VertexBufferLayout.hpp>
#include <glw/IndexBuffer.hpp>
#include <glw/Shader.hpp>

#include <utils/cell_index.h>
#include <utils/color.h>
#include <utils/point.h>

#include "storage.h"

using IndexStorage = std::vector<unsigned int>;

class GraphicsData {
public:
    using VertexBuffer = glw::VertexBuffer<Vertex>;

    GraphicsData(ut::NormalizedIndex size);

    void update();

    size_t pushVertex(ut::Pointf point, const ut::Color color);

    void pushPolygon(size_t vertex1Id, size_t vertex2Id, size_t vertex3Id);

private:
public:
    GraphicsData(ut::NormalizedIndex size, size_t cellRows, size_t cellCols);

    VertexBuffer v;
    glw::VertexArray va;
    glw::IndexBuffer i;
    glw::Shader shader;
};
