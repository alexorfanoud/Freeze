#include <glad/glad.h>

#include "misc.hpp"

std::string TranslateErrorCode(unsigned int code){
    switch (code)
    {
    case 1280:
        return "GL_INVALID_ENUM";
    case 1281:
        return "GL_INVALID_VALUE"; 
    case 1282:
        return "GL_INVALID_OPERATION";
    case 1283:
        return "GL_STACK_OVERFLOW";
    case 1284:
        return "GL_STACK_UNDERFLOW";
    case 1285:
        return "GL_OUT_OF_MEMORY";
    case 1286:
        return "GL_INVALID_FRAMEBUFFER_OPERATION";
    case 1287:
        return "GL_CONTEXT_LOST";
    case 1288:
        return "GL_TABLE_TOO_LARGE";
    default:
        return "Invalid Code: " + std::to_string(code);
    }
}

void ClearError() {
    while(glGetError() != GL_NO_ERROR );
}
void PrintError(std::string func, std::string file, int line){
    GLenum err = glGetError();
    if(err != GL_NO_ERROR){
        std::cout << "Function: " << func << std::endl;
        std::cout << "File: " << file << ':' << line << std::endl;
        std::cout << "[ERROR: " << TranslateErrorCode(err) << "]" << std::endl;

        raise(SIGTRAP);
    }
}
