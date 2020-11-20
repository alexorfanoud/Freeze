#pragma once

namespace Freeze{
    enum  class EventType{
        None = 0,
        MouseMove, MouseClick, MouseRelease, 
        KeyPress, KeyRelease,
        WindowClose, WindowResize,
    };

    class Event
    {
    public:
        virtual EventType GetType() const { return EventType::None; }
        virtual std::string GetName() const { return "EventType::None";}
    };
}
