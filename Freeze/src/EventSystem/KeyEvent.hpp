#pragma once 

#include "Base.hpp"
#include "Event.hpp"

namespace Freeze {
    class KeyPressedEvent : public Event{
    public:
        KeyPressedEvent(int code, bool repeat = false) : m_Code(code), m_Repeat(repeat){}
        inline int GetKeyCode() const { return m_Code; }      
        inline bool IsRepeat() const { return m_Repeat; }      

        EVENT_TYPE(EventType::KeyPress);
    private:
        int m_Code;
        bool m_Repeat;
    };

    class KeyReleasedEvent : public Event{
    public:
        KeyReleasedEvent(int code) : m_Code(code){}
        inline int GetKeyCode() const { return m_Code; }      

        EVENT_TYPE(EventType::KeyRelease);
    private:
        int m_Code;
    };
}