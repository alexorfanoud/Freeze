cmake_minimum_required(VERSION 3.13)
project(Sandbox)

set(root_dir "${CMAKE_SOURCE_DIR}")
set(SandboxDir "${Sandbox_SOURCE_DIR}")
file(GLOB src_files "${SandboxDir}/src/*.cpp")

add_executable(SandboxExec "${src_files}")

target_include_directories(SandboxExec PUBLIC "${root_dir}/Freeze/")