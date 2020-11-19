#include "vertexArray.hpp"
#include "indexBuffer.hpp"
#include "vertexBuffer.hpp"

class Renderer{

public:
    ~Renderer();
    int Setup();
    void Clear() const;
    void Draw(const VertexArray& vao, const VertexBuffer& vbo);
    void Draw(const VertexArray& vao, const VertexBuffer& vbo, const IndexBuffer& ibo);
    inline GLFWwindow* GetWindow() const { return m_window; };
private:
    GLFWwindow* m_window;
};