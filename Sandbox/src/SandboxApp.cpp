#include "Freeze.hpp"

class Sandbox : public Freeze::Application
{
};

namespace Freeze
{
    Freeze::Application *CreateApplication()
    {
        return new Sandbox();
    }
} // namespace Freeze
