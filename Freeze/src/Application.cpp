#include "Application.hpp"
#include "Core.hpp"
#include "spdlog/spdlog.h"

namespace Freeze
{
    Application::Application()
    :m_Running(true)
    {
        m_Window = new Window();
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