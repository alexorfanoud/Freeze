#include "glad/glad.h"

#include "Application.hpp"
#include "Core.hpp"
#include "spdlog/spdlog.h"

namespace Freeze
{
    bool Application::OnMouseMove(MouseMoveEvent& ev){
        std::cout << ev.GetName() << ": " << ev.GetXPos() << ' ' << ev.GetYPos() << '\n';
        //TODO SEND MOVEMENT TO CAMERA
        return true;
    }
    bool Application::OnMouseClick(MouseClickEvent& ev){
        std::cout << ev.GetName() << ": " << ev.GetKeyCode() << std::endl;;
        //TODO SEND MOVEMENT TO CAMERA
        return true;
    }
    bool Application::OnMouseRelease(MouseReleaseEvent& ev){
        std::cout << ev.GetName() << ": " << ev.GetKeyCode() << std::endl;;
        //TODO SEND MOVEMENT TO CAMERA
        return true;
    }
    bool Application::OnWindowClose(WindowCloseEvent& ev){
        std::cout << ev.GetName() << std::endl;
        m_Running = false;
        return true;
    }
    bool Application::OnWindowResize(WindowResizeEvent& ev){
       //TODO handle window resize
        std::cout << ev.GetName() << std::endl;
        return true;
    }
    bool Application::OnKeyPress(KeyPressedEvent& ev){
        //TODO handle key input
        std::cout << ev.GetName() << std::endl;
        return true;
    }
    bool Application::OnKeyRelease(KeyReleasedEvent& ev){
        //TODO handle key input
        std::cout << ev.GetName() << std::endl;
        return true;
    }
    bool Application::OnKeyRepeat(KeyRepeatEvent& ev){
        //TODO handle key input
        std::cout << ev.GetName() << std::endl;
        return true;
    }
    void Application::SetEventListeners(){
        EventHandler::AttachListener<MouseMoveEvent>(BIND_EVENT_FUNC(Application::OnMouseMove));
        EventHandler::AttachListener<MouseClickEvent>(BIND_EVENT_FUNC(Application::OnMouseClick));
        EventHandler::AttachListener<MouseReleaseEvent>(BIND_EVENT_FUNC(Application::OnMouseRelease));
        EventHandler::AttachListener<WindowCloseEvent>(BIND_EVENT_FUNC(Application::OnWindowClose));
        EventHandler::AttachListener<WindowResizeEvent>(BIND_EVENT_FUNC(Application::OnWindowResize));
        EventHandler::AttachListener<KeyPressedEvent>(BIND_EVENT_FUNC(Application::OnKeyPress));
        EventHandler::AttachListener<KeyReleasedEvent>(BIND_EVENT_FUNC(Application::OnKeyRelease));
        EventHandler::AttachListener<KeyRepeatEvent>(BIND_EVENT_FUNC(Application::OnKeyRepeat));
    }

    Application::Application()
    :m_Running(true),
    m_Window(new Window())
    {
        Init();
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

    void Application::Init(){
        SetEventListeners();
        if (!gladLoadGL())
        {
            printf("Something went wrong!\n");
            exit(-1);
        }
    }

} // namespace Freeze