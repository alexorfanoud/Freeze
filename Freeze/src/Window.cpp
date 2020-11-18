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

        SetCallbacks();

        return 0;
    }
    void Window::SetCallbacks(){
        //MouseMovement
        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos){
            MouseMoveEvent event(xpos, ypos);
            EventHandler::ResolveEvent(event);
        });
        //MouseClick
        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods) {
            switch (action)
            {
            case GLFW_PRESS:
            {
                MouseClickEvent event(button);
                EventHandler::ResolveEvent(event);
                break;
            }

            case GLFW_RELEASE:
            {
                MouseReleaseEvent event(button);
                EventHandler::ResolveEvent(event);
                break;
            }
            default:
                break;
            }
        });
        //WindowClose
        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window){
            WindowCloseEvent event;
            EventHandler::ResolveEvent(event);
        });
        //WindowResize
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height){
            WindowResizeEvent event(width, height);
            EventHandler::ResolveEvent(event);
        });
        //KeyInputs
        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
            switch (action)
            {
            case GLFW_PRESS:
            {
                KeyPressedEvent event(key);
                EventHandler::ResolveEvent(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event(key);
                EventHandler::ResolveEvent(event);
                break;
            }
            case GLFW_REPEAT:
            {
                KeyRepeatEvent event(key);
                EventHandler::ResolveEvent(event);
                break;
            }
            default:
            {
                break;
            }
            }
        });
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