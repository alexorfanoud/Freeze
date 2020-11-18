#pragma once

#include "Event.hpp"

namespace Freeze{
    class MouseMoveEvent : public Event{
    public:
        MouseMoveEvent(double xpos, double ypos)
        :m_Xpos(xpos), m_Ypos(ypos){}
        inline double GetXPos() const { return m_Xpos; }
        inline double GetYPos() const { return m_Ypos; }

        EVENT_TYPE(EventType::MouseMove);
    private:
       double m_Xpos, m_Ypos; 
    };

    class MouseClickEvent : public Event{
    public:
        MouseClickEvent(int button): m_Button(button){};
        inline int GetKeyCode() const { return m_Button; }
        
        EVENT_TYPE(EventType::MouseClick);
    private:
        int m_Button;
    };

    class MouseReleaseEvent : public Event{
    public:
        MouseReleaseEvent(int button) : m_Button(button) {};
        inline int GetKeyCode() const { return m_Button; }

        EVENT_TYPE(EventType::MouseRelease);
    private:
        int m_Button;
    };
}

