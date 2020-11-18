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
        void Init();
        bool OnMouseMove(MouseMoveEvent& ev);
        bool OnMouseClick(MouseClickEvent& ev);
        bool OnMouseRelease(MouseReleaseEvent& ev);
        bool OnWindowClose(WindowCloseEvent& ev);
        bool OnWindowResize(WindowResizeEvent& ev);
        bool OnKeyPress(KeyPressedEvent& ev);
        bool OnKeyRelease(KeyReleasedEvent& ev);
        bool OnKeyRepeat(KeyRepeatEvent& ev);
        void SetEventListeners();
    };
} // namespace Freeze