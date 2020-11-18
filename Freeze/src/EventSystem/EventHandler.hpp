#pragma once

#include "pch.hpp"
#include "Event.hpp"

namespace Freeze{

    class EventHandler {
    public:
        EventHandler(const EventHandler&) = delete;
        static EventHandler& Get();
        static bool ResolveEvent(Event &ev);

        template<typename T>
        static void AttachListener(std::function<bool(T &)> fn) { return Get().AttachListenerImpl<T>(fn); }
    private:
        EventHandler() ;
        bool ResolveEventImpl(Event& ev);

        template <typename T>
        void AttachListenerImpl(std::function<bool(T &)> fn)
        {
            Listeners[T::GetStaticType()].push_back(OnEventWrapper<T>(fn));
        };

        template <typename T>
        std::function<bool(Event &)> OnEventWrapper(const std::function<bool(T &)> &fn)
        {
            return [=](Event &ev) {
                auto ev_ptr = static_cast<T *>(&ev);
                return fn(*ev_ptr);
            };
        };
        std::unordered_map<EventType, std::vector<std::function<bool(Event&)>>> Listeners;
    };
}