#pragma once

#include "Application.hpp"
namespace Freeze
{
    extern Freeze::Application *CreateApplication();
}

int main()
{
    auto app = Freeze::CreateApplication();
    app->Run();
    delete app;
}