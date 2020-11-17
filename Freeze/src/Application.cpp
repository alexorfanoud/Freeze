#include "Application.hpp"
#include "Core.hpp"
#include "spdlog/spdlog.h"

namespace Freeze
{
    void Application::OnMouseMove(MouseMoveEvent& ev){
        std::cout << ev.GetXPos() << ' ' << ev.GetYPos() << '\n';
        //TODO SEND MOVEMENT TO CAMERA
    }
    void Application::OnWindowClose(WindowCloseEvent& ev){
        m_Running = false;
    }
    void Application::OnWindowResize(WindowResizeEvent& ev){
       //TODO handle window resize
    }
    void Application::OnKeyPress(KeyPressedEvent& ev){
        //TODO handle key input
        std::cout << "key pressed" << std::endl;
    }
    void Application::OnKeyRelease(KeyReleasedEvent& ev){
        //TODO handle key input
    }
    void Application::OnEvent(Event& event) {
        Dispatcher dispatcher(&event);
        dispatcher.Dispatch<MouseMoveEvent>(BIND_EVENT_FUNC(Application::OnMouseMove));
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNC(Application::OnWindowResize));
        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNC(Application::OnKeyPress));
        dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FUNC(Application::OnKeyRelease));
    }

    Application::Application()
    :m_Running(true)
    {
        m_Window = new Window();
        m_Window->SetOnEventFunction(BIND_EVENT_FUNC(Application::OnEvent));
    }
    Application::~Application()
    {
        Shutdown();
    }
    void Application::Shutdown()
    {
        delete m_Window;
    }

    void Application::Run()
    {
        spdlog::info("Running...");
        while (m_Running)
        {
            m_Window->Update();
        }
    }

} // namespace Freeze