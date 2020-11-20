#include <glad/glad.h>
#include "vertexBuffer.hpp"
#include "misc.hpp"

namespace Freeze
{
    VertexBuffer::VertexBuffer() : m_RendererID(0), m_Count(0)
    {
        glCall(glGenBuffers(1, &m_RendererID));
    }

    VertexBuffer::~VertexBuffer()
    {
        glCall(glDeleteBuffers(1, &m_RendererID));
    }

    void VertexBuffer::Bind() const
    {
        glCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    }

    void VertexBuffer::Unbind() const
    {
        glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    void VertexBuffer::AddData(unsigned int size, const void *data, unsigned int count)
    {
        Bind();
        m_Count = count;
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

} // namespace Freeze