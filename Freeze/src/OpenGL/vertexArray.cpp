#include <glad/glad.h>
#include "vertexArray.hpp"
#include "misc.hpp"
#include "pch.hpp"

VertexArray::VertexArray() : m_RendererID(0) {
    glCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray() {
    glCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::Bind() const {
    glCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const {
    glCall(glBindVertexArray(0));
}

void VertexArray::AddLayout(const AttributeLayout &layout) const {
    Bind();
    unsigned int index = 0;
    size_t offset = 0;
    for(const auto& attr : layout.GetAttributes()){
        glCall(glEnableVertexAttribArray(index));
        glCall(glVertexAttribPointer(index++, attr.GetCount(), attr.GetType(), GL_FALSE, layout.GetStride(), (const void*)offset));
        offset += attr.GetCount() * attr.GetSize();
    }
}
