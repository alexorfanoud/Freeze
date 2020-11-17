#pragma once

namespace Freeze{
    enum  class EventType{
        None = 0,
        MouseMove,
        KeyPress, KeyRelease, 
        WindowClose, WindowResize,
    };

    class Event
    {
    public:
        virtual EventType GetType() const { return EventType::None; }
    };
}
