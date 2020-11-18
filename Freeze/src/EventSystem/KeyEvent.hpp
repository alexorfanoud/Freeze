#include "Base.hpp"
#include "Event.hpp"

namespace Freeze {
    class KeyPressedEvent : public Event{
    public:
        KeyPressedEvent(int code) : m_Code(code){}
        EVENT_TYPE(EventType::KeyPress);
    private:
        int m_Code;
    };

    class KeyReleasedEvent : public Event{
    public:
        KeyReleasedEvent(int code) : m_Code(code){}
        EVENT_TYPE(EventType::KeyRelease);
    private:
        int m_Code;
    };

    class KeyRepeatEvent : public Event{
    public:
        KeyRepeatEvent(int code) : m_Code(code){}
        EVENT_TYPE(EventType::KeyRepeat);
    private:
        int m_Code;
    };

}