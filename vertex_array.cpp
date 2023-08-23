#include "vertex_array.h"

#include "debug.h"

namespace {

auto genVertexArray() {
    unsigned int result{};
    GLCALL(glGenVertexArrays(1, &result));
    return result;
}

} // namespace

VertexArray::VertexArray()
    : id{genVertexArray()}
{}

VertexArray::~VertexArray() {
    GLCALL(glDeleteVertexArrays(1, &id));
}

void VertexArray::addBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout) {
    bind();
    buffer.bind();

    const auto& elements = layout.getElements();
    for (int i = 0; i < elements.size(); ++i) {
        const auto& element = elements[i];
        GLCALL(glEnableVertexAttribArray(i));
        GLCALL(glVertexAttribPointer(
                    i,
                    element.count,
                    element.type,
                    element.normalized,
                    layout.getStride(),
                    (void*)element.offset
                ));
    }
}

void VertexArray::bind() const {
    GLCALL(glBindVertexArray(id));
}

void VertexArray::unbind() const {
    GLCALL(glBindVertexArray(0));
}
