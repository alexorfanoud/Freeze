#pragma once

#include "pch.hpp"
#include "../Core.hpp"

#define glCall(x) ClearError(); x; PrintError(#x, __FILE__, __LINE__);

namespace Freeze {
    std::string TranslateErrorCode(unsigned int code);
    void ClearError();
    void PrintError(std::string func, std::string file, int line);
}


