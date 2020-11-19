#include "pch.hpp"

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include "misc.hpp"
#include "renderer.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glCall(glViewport(0, 0, width, height));
} 

Renderer::~Renderer() {
    glfwTerminate();
}

int Renderer::Setup() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    m_window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }  

    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glViewport(0, 0, 800, 800); //origin and viewport dimensions
    glEnable(GL_DEPTH_TEST);   
    return 0;
}

void Renderer::Clear() const {

    glCall(glClearColor(0.2f, 0.4f, 0.4f, 1.0f));
    glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& vao, const VertexBuffer& vbo){
    vao.Bind();
    vbo.Bind();
    glCall(glDrawArrays(GL_TRIANGLES, 0, vbo.GetCount()));
}

void Renderer::Draw(const VertexArray& vao, const VertexBuffer& vbo, const IndexBuffer& ibo){
    vao.Bind();
    vbo.Bind();
    ibo.Bind();
    glCall(glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));
}   