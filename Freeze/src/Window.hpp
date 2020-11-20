#pragma once 

#include "pch.hpp"
#include "EventSystem/Base.hpp"
#include "pch.hpp"
#include "Core.hpp"
#include <GLFW/glfw3.h>

namespace  Freeze {
    class Window {
    public:
    public:
        Window(unsigned int width = FZ_DEFAULT_WINDOW_WIDTH, unsigned int height = FZ_DEFAULT_WINDOW_HEIGHT, std::string title = "FreezeEngine");
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