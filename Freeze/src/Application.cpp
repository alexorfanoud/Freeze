#include <iostream>
#include "Application.hpp"
#include "Core.hpp"
#include "spdlog/spdlog.h"

namespace Freeze
{
    void Application::Run()
    {
        spdlog::info("Hello running...");
        while (1)
            ;
    }
} // namespace Freeze