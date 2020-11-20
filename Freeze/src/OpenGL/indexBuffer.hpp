#pragma once

#include "pch.hpp"

namespace Freeze
{
    class IndexBuffer
    {

    public:
        IndexBuffer();
        ~IndexBuffer();
        void Bind() const;
        void Unbind() const;
        void AddData(unsigned int size, const void *data, unsigned int count);
        template<typename T>
        void AddData(std::vector<T> data, unsigned int count) {
            Bind();
            m_Count = count;
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data[0]) * data.size(), &data[0], GL_STATIC_DRAW);
        }
        inline unsigned int GetCount() const { return m_Count; }

    private:
        unsigned int m_RendererID;
        unsigned int m_Count;
    };

} // namespace Freeze
