#pragma once 

#include<iostream>

template<typename ... Args >
void PrintArgs(Args&&... args){
    (std::cout << ... << args ) << std::endl;
}

//----------Macros--------------//
#ifdef __unix__
    #include <signal.h>
    #define ASSERT(x, ... ) if( !(x) ) {PrintArgs("[ASSERT ERROR: ", ##__VA_ARGS__, "]\n", __FUNCTION__, '\n', __FILE__, ": ", __LINE__); raise(SIGTRAP);}
#endif
#define BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)

//-------Constants--------------//
#define FZ_EVENT_RESOLVED true
#define FZ_EVENT_UNRESOLVED false
//CameraController
#define FZ_DEFAULT_SENS_X 5.0f
#define FZ_DEFAULT_SENS_Y 5.0f
#define FZ_DEFAULT_CAM_MOVESPEED 20.0f
#define FZ_PITCH_MAX 80.0f
#define FZ_PITCH_MIN -80.0f
//Window
#define FZ_DEFAULT_WINDOW_WIDTH 1280.0f
#define FZ_DEFAULT_WINDOW_HEIGHT 960.0f
//TODO FREEZE CUSTOM KEYMAPS