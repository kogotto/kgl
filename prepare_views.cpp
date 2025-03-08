#include "prepare_views.h"

#include <glw/Debug.hpp>
#include <utils/rect.h>

namespace {

inline void insertVertex(Storage& storage, float x, float y) {
    storage.push_back({
        {x, y}, {/*1.f, 1.f, 1.f, 1.f*/}
    });
}

inline void insertRect(Storage& storage, float left, float top, float sizeX, float sizeY) {
    const auto right = left + sizeX;
    const auto bottom = top + sizeY;
    insertVertex(storage, left, top);
    insertVertex(storage, right, top);
    insertVertex(storage, left, bottom);
    insertVertex(storage, right, bottom);
}

inline auto prepareVertexStorage(size_t rows, size_t cols) {
    const size_t verticesCount = 4 * rows * cols;
    Storage result;
    result.reserve(verticesCount);

    for (size_t i = 0; i < verticesCount; ++i) {
        result.push_back({});
    }

    return result;
}

auto prepareVertexArray(const glw::VertexBufferHandler& vb) {
    glw::VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(4);

    glw::VertexArray va;
    va.addBuffer(vb, layout);

    return va;
}

using IndexStorage = std::vector<unsigned int>;

inline auto prepareIndexStorage(size_t rows, size_t cols) {
    IndexStorage result;
    const auto cellCount = rows * cols;
    constexpr size_t polygonsPerCell = 2;
    constexpr size_t verticesPerPolygon = 3;
    result.resize(cellCount * polygonsPerCell * verticesPerPolygon);

    return result;
}

const ut::Rect screenRect{-0.7f, 0.7f, 0.7f, -0.7f};

} // namespace

GraphicsData::GraphicsData(ut::NormalizedIndex size)
    : GraphicsData(
        size,
        size.row,
        size.col)
{}

void GraphicsData::update() {
    v.update();
    i.update();
}

size_t GraphicsData::pushVertex(ut::Pointf point, const ut::Color color) {
    v.storage().push_back({
        {point.x, point.y},
        {color[0], color[1], color[2], color[3]}
    });

    return v.storage().size() - 1;
}

void GraphicsData::pushPolygon(size_t vertex1Id, size_t vertex2Id, size_t vertex3Id) {
    i.storage().push_back(vertex1Id);
    i.storage().push_back(vertex2Id);
    i.storage().push_back(vertex3Id);
}

GraphicsData::GraphicsData(
        ut::NormalizedIndex size,
        size_t cellRows,
        size_t cellCols)
    : v{prepareVertexStorage(cellRows, cellCols)}
    , va{prepareVertexArray(v.handler())}
    , i{prepareIndexStorage(cellRows, cellCols)}
    , shader(glw::Shader::fromFile("res/shaders/automata.shader"))
{
}
