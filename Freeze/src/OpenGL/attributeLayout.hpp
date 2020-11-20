#pragma once

#include "pch.hpp"
namespace Freeze
{
    class Attribute
    {
    public:
        Attribute(unsigned int count, unsigned int tsize, unsigned int type)
            : m_count(count), m_typeSize(tsize), m_type(type){};

        inline unsigned int GetSize() const { return m_typeSize; }
        inline unsigned int GetCount() const { return m_count; }
        inline unsigned int GetType() const { return m_type; }

    private:
        unsigned int m_count, m_typeSize;
        unsigned int m_type;
    };

    class AttributeLayout
    {
    public:
        AttributeLayout() : m_totalSize(0){};
        template <typename T>
        void AddAttribute(unsigned int count);

        inline std::vector<Attribute> GetAttributes() const { return m_attributes; }
        inline unsigned int GetStride() const { return m_totalSize; }

    private:
        unsigned int m_totalSize;
        std::vector<Attribute> m_attributes;
    };

} // namespace Freeze