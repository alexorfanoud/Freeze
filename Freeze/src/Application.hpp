#pragma once

#include "Window.hpp"

namespace Freeze
{
    class Application
    {
    public:
        Application();
        ~Application();
        void Run();
    private:
        bool m_Running;
        Window* m_Window;
    private:
        void Shutdown();
    };
} // namespace Freeze