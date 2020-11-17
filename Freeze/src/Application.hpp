#pragma once

#include "Window.hpp"
#include "EventSystem/Base.hpp"

namespace Freeze
{
    class Application
    {
    public:
        Application();
        ~Application();
        void Run();
        void OnEvent(Event& event);
    private:
        bool m_Running;
        Window* m_Window;
    private:
        void Shutdown();
        void OnMouseMove(MouseMoveEvent& ev);
        void OnWindowClose(WindowCloseEvent& ev);
        void OnWindowResize(WindowResizeEvent& ev);
        void OnKeyPress(KeyPressedEvent& ev);
        void OnKeyRelease(KeyReleasedEvent& ev);
    };
} // namespace Freeze