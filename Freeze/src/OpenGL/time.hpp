#include <GLFW/glfw3.h>

namespace Freeze
{

    class Time
    {
    public:
        Time() : m_currentFrame(0.0f){};
        inline void Reset() { m_currentFrame = glfwGetTime(); }
        inline float DeltaTime()
        {
            float currentTime = glfwGetTime();
            float delta = currentTime - m_currentFrame;
            m_currentFrame = currentTime;
            return delta;
        }

    private:
        float m_currentFrame;
    };
} // namespace Freeze