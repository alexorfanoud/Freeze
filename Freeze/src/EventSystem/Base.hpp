#pragma once 

#define EVENT_TYPE(x) \
        inline std::string GetName() const override { return #x; }\
        inline EventType GetType() const override { return GetStaticType(); };\
        inline static EventType GetStaticType() { return x; } 

#include "Dispatcher.hpp"
#include "Event.hpp"
#include "MouseEvent.hpp"
#include "WindowEvent.hpp"
#include "KeyEvent.hpp"
#include "EventHandler.hpp"