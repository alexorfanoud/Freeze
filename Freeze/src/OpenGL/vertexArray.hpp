#pragma once

#include "attributeLayout.hpp"

class VertexArray{
public:
    VertexArray();
    ~VertexArray();
    void Bind() const;
    void Unbind() const;
    void AddLayout(const AttributeLayout& layout) const;
private:
    unsigned int m_RendererID;
};