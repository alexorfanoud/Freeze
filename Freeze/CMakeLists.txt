cmake_minimum_required(VERSION 3.13)
project(Freeze)

set(root_dir "${CMAKE_SOURCE_DIR}")
set(FreezeDir "${Freeze_SOURCE_DIR}")
set(vendor_dir "${FreezeDir}/vendor")
file(GLOB src_files "${FreezeDir}/src/*.cpp")
file(GLOB header_files "${FreezeDir}/src/*.hpp")

add_library(FreezeDLL STATIC
    "${src_files}"
    "${header_files}"
)

target_include_directories(FreezeDLL PRIVATE
     "${FreezeDir}"
     "${vendor_dir}/spdlog/include"
     )

add_subdirectory("${vendor_dir}/spdlog")
target_link_libraries(FreezeDLL PRIVATE spdlog::spdlog)