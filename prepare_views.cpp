#include "prepare_views.h"

#include <glw/debug.h>

namespace {

struct Rect {
    float left;
    float top;
    float right;
    float bottom;
};

inline float step(float start, float finish, size_t count) {
    return (finish - start) / count;
}

inline float ratio(size_t index, size_t count) {
    return static_cast<float>(index) / count;
}

inline float linearInterpolation(float start, float finish, float ratio) {
    return start + (finish - start) * ratio;
}

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

inline auto prepareVertexStorage(size_t rows, size_t cols, const Rect& rect) {
    Storage result;
    result.reserve(4 * rows * cols);

    const float stepX = step(rect.left, rect.right, cols);
    const float stepY = step(rect.top, rect.bottom, rows);

    for (size_t row = 0; row < rows; ++row) {
        const auto verticalRatio = ratio(row, rows);
        for (size_t col = 0; col < cols; ++col) {
            const auto horizontalRatio = ratio(col, cols);
            const auto left = linearInterpolation(
                rect.left,
                rect.right,
                horizontalRatio
            );
            const auto top = linearInterpolation(
                rect.top,
                rect.bottom,
                verticalRatio
            );
            insertRect(result, left, top, stepX, stepY);
        }
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
    result.reserve(cellCount * polygonsPerCell * verticesPerPolygon);

    for (size_t cell = 0; cell < cellCount; ++cell) {
        const auto topLeft = 4 * cell;
        const auto topRight = topLeft + 1;
        const auto bottomLeft = topRight + 1;
        const auto bottomRight = bottomLeft + 1;

        // First polygon
        result.push_back(topLeft);
        result.push_back(topRight);
        result.push_back(bottomLeft);
        // Second polygon
        result.push_back(topRight);
        result.push_back(bottomRight);
        result.push_back(bottomLeft);
    }

    return result;
}

const Rect screenRect{-0.7f, 0.7f, 0.7f, -0.7f};

} // namespace

GraphicsData::GraphicsData(ut::NormalizedIndex size)
    : GraphicsData(
        size,
        size.row,
        size.col)
{}

void GraphicsData::update(const ca::FieldModel& field) {
    fieldView.update(field);

    v.update();
}

GraphicsData::GraphicsData(
        ut::NormalizedIndex size,
        size_t cellRows,
        size_t cellCols)
    : v{prepareVertexStorage(cellRows, cellCols, screenRect)}
    , va{prepareVertexArray(v.handler())}
    , i{prepareIndexStorage(cellRows, cellCols)}
    , shader(glw::Shader::fromFile("res/shaders/automata.shader"))
    , fieldView(size, v.storage())
{
}
