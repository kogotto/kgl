#pragma once

#include <vector>

#include <field.h>
#include "storage.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
#include "index_buffer.h"
#include "shader.h"

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
