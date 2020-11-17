#pragma once

#include "Event.hpp"

namespace Freeze{
    class WindowCloseEvent : public Event{
    public:
    
        EVENT_TYPE(EventType::WindowClose);
    private:

    };


    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(int w, int h) : m_Width(w), m_Height(h) {}
        EVENT_TYPE(EventType::WindowResize);
        inline int GetWidth() const { return m_Width; }
        inline int GetHeight() const { return m_Height; }
    private:
        int m_Width, m_Height;
    };
}