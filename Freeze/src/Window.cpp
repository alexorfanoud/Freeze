#include "Core.hpp"
#include "Window.hpp"


namespace Freeze {
    Window::Window(unsigned int width, unsigned int height, std::string title)
    : m_Width(width), m_Height(height), m_DisplayTitle(title)
    {
        int status = Init();
        ASSERT(status != -1);
    }
    Window::~Window()
    {
        Shutdown();
    }

    int Window::Init()
    {
        if(!glfwInit()) return -1;
        m_Window = glfwCreateWindow(m_Width, m_Height, m_DisplayTitle.c_str(), NULL, NULL);
        if (!m_Window)
        {
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(m_Window);
        return 0;
    }
    void Window::Shutdown()
    {
        glfwTerminate();
    }

    void Window::Update()
    {
        glClearColor(0.5f, 0.2f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(m_Window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}