#include "EventHandler.hpp"

namespace Freeze{
    EventHandler::EventHandler(){};
    EventHandler& EventHandler::Get(){
        static EventHandler instance;
        return instance;
    }
    bool EventHandler::ResolveEvent(Event &ev) { return Get().ResolveEventImpl(ev); }

    bool EventHandler::ResolveEventImpl(Event &ev)
    {
        bool resolved = false;
        for (auto &fnListener : Listeners[ev.GetType()])
        {
            resolved |= fnListener(ev);
            if (resolved)
                break;
        }
        return resolved;
    }

}