#pragma once 

#include "pch.hpp"
#include "EventSystem/Base.hpp"
#include<functional>
#include <GLFW/glfw3.h>

namespace  Freeze {
    class Window {
    public:
    public:
        Window(unsigned int width = 640, unsigned int height = 480, std::string title = "FreezeEngine");
        ~Window();
        void Update();
    private:
        unsigned int m_Width, m_Height;
        std::string m_DisplayTitle;
        GLFWwindow* m_Window;
    private:
        int Init();
        void Shutdown();
        void SetCallbacks();
    };
}