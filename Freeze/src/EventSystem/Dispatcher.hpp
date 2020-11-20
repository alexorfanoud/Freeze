#pragma once 

#include "Event.hpp"
#include <functional>

namespace Freeze{
    class Dispatcher{
    using EventFn = typename std::function<void(Event&)>;
    public:
        Dispatcher(Event* event) : m_Event(event) {}
        template<typename T>
        void Dispatch(std::function<void(T&)> fn){
            if(m_Event->GetType() == T::GetStaticType()) fn(static_cast<T&>(*m_Event));
        }
    private:
        Event* m_Event;
    };
}