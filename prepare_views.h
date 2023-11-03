#pragma once

#include "storage.h"
#include <glw/vertex_array.h>
#include <glw/vertex_buffer_handler.h>
#include <glw/vertex_buffer_layout.h>
#include <glw/index_buffer.h>
#include <glw/shader.h>

#include <utils/cell_index.h>
#include <field_model.h>

#include "field_view.h"

using IndexStorage = std::vector<unsigned int>;

class GraphicsData {
public:
    GraphicsData(ut::NormalizedIndex size);

    void update(const ca::FieldModel& field);

private:
public:
    GraphicsData(ut::NormalizedIndex size, size_t cellRows, size_t cellCols);

    Storage storage;
    glw::VertexBuffer vb;
    glw::VertexArray va;
    IndexStorage indices;
    glw::IndexBuffer ib;
    glw::Shader shader;
    FieldView fieldView;
};
