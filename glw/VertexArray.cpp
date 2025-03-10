#include <glw/VertexArray.hpp>

#include <utility>

#include <glw/Debug.hpp>

#include <glw/VertexBufferHandler.hpp>
#include <glw/VertexBufferLayout.hpp>

namespace glw {

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

VertexArray::VertexArray(VertexArray&& rhs) noexcept
    : id{std::exchange(rhs.id, 0)}
{}

VertexArray& VertexArray::operator=(VertexArray&& rhs) noexcept {
    std::swap(id, rhs.id);
    return *this;
}

VertexArray::~VertexArray() {
    GLCALL(glDeleteVertexArrays(1, &id));
}

void VertexArray::addBuffer(const VertexBufferHandler& buffer, const VertexBufferLayout& layout) {
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

} // namespace glw
