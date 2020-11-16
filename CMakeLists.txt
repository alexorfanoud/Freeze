cmake_minimum_required(VERSION 3.13)
project(FreezeEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(FreezePath "${CMAKE_SOURCE_DIR}/Freeze")
set(SandboxPath "${CMAKE_SOURCE_DIR}/Sandbox")

add_subdirectory("${FreezePath}")
add_subdirectory("${SandboxPath}")

target_link_libraries(SandboxExec FreezeLib)