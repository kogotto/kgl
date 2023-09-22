#pragma once

#include <vector>

#include <field.h>
#include "storage.h"
#include <glw/vertex_array.h>
#include <glw/vertex_buffer.h>
#include <glw/vertex_buffer_layout.h>
#include <glw/index_buffer.h>
#include <glw/shader.h>

#include "field_view.h"

using IndexStorage = std::vector<unsigned int>;

class GraphicsData {
public:
    GraphicsData(const Field& fieldModel);

    void update();

private:
public:
    GraphicsData(const Field& fieldModel, size_t cellRows, size_t cellCols);

    Storage storage;
    VertexBuffer vb;
    VertexArray va;
    IndexStorage indices;
    IndexBuffer ib;
    Shader shader;
    FieldView fieldView;
};
