#include <GLFW/glfw3.h>
#include "attributeLayout.hpp"

template <>
void AttributeLayout::AddAttribute<float>(unsigned int count)
{
    Attribute attr(count, sizeof(float), GL_FLOAT);
    m_attributes.push_back(attr);
    m_totalSize += sizeof(float) * count;
}


template <>
void AttributeLayout::AddAttribute<int>(unsigned int count)
{
    Attribute attr(count, sizeof(int), GL_INT);
    m_attributes.push_back(attr);
    m_totalSize += sizeof(int) * count;
}