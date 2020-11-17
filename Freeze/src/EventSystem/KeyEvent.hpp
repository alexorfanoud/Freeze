#include "Base.hpp"
#include "Event.hpp"

namespace Freeze {
    class KeyPressedEvent : public Event{
    public:
        KeyPressedEvent(int code, int repeat = 0) : m_Code(code), m_Repeat(repeat) {}
        EVENT_TYPE(EventType::KeyPress);
    private:
        int m_Code, m_Repeat;
    };

    class KeyReleasedEvent : public Event{
    public:
        KeyReleasedEvent(int code) : m_Code(code){}
        EVENT_TYPE(EventType::KeyRelease);
    private:
        int m_Code;
    };
}