#pragma once

class IndexBuffer{

public:
    IndexBuffer();
    ~IndexBuffer();
    void Bind() const;
    void Unbind() const;
    void AddData(unsigned int size, const void* data, unsigned int count);
    inline unsigned int GetCount() const { return m_Count; }
private:
    unsigned int m_RendererID;
    unsigned int m_Count;
};
