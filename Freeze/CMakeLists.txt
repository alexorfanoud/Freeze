cmake_minimum_required(VERSION 3.13)
project(Freeze)

set(root_dir "${CMAKE_SOURCE_DIR}")
set(FreezeDir "${Freeze_SOURCE_DIR}")
set(vendor_dir "${FreezeDir}/vendor")
file(GLOB src_files 
    "${FreezeDir}/src/*.cpp"
    "${FreezeDir}/src/EventSystem/*.cpp"
    "${FreezeDir}/vendor/glad/src/glad.c"
    )
file(GLOB header_files 
    "${FreezeDir}/src/*.hpp"
    "${FreezeDir}/src/EventSystem/*.hpp"
    )

#Freeze Library
add_library(FreezeLib STATIC
    "${src_files}"
    "${header_files}"
)

#Dependencies
    #LOGGING : spdlog
    add_subdirectory("${vendor_dir}/spdlog")
    target_link_libraries(FreezeLib spdlog::spdlog)
    #glfw
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    add_subdirectory("${vendor_dir}/glfw")
    target_link_libraries(FreezeLib glfw)
    #OPENGL
    find_package(OpenGL REQUIRED)
    target_link_libraries(FreezeLib OpenGL::GL)

#Includes
target_include_directories(FreezeLib PRIVATE
     "${FreezeDir}"
     "${vendor_dir}/spdlog/include"
     "${vendor_dir}/glfw/include"
     "${vendor_dir}/glad/include"
     )

#Precompiled Headers ------Requires CMAKE 3.16 OR HIGHER----------
# target_precompile_headers(FreezeLib "${FreezeDir}/pch.hpp")


