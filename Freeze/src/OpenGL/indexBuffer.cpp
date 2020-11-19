#include <glad/glad.h>
#include "indexBuffer.hpp"
#include "misc.hpp"

IndexBuffer::IndexBuffer() : m_RendererID(0), m_Count(0) {
    glCall(glGenBuffers(1, &m_RendererID));
}

IndexBuffer::~IndexBuffer() {
    glCall(glDeleteBuffers(1, &m_RendererID));
}


void IndexBuffer::Bind() const {
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const {
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::AddData(unsigned int size, const void* data, unsigned int count){
    Bind();
    m_Count = count;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}