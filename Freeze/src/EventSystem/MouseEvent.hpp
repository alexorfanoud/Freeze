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
}

