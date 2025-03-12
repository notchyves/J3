cmake_minimum_required(VERSION 3.30)
project(j3)

include(FetchContent)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_UNITY_BUILD TRUE)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.15.1
)

FetchContent_Declare(
        entt
        GIT_REPOSITORY https://github.com/skypjack/entt.git
        GIT_TAG v3.14.0
)

FetchContent_MakeAvailable(spdlog entt)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp")
include_directories(src)

add_executable(j3 WIN32 ${SOURCES})

target_precompile_headers(j3 PRIVATE src/common.hpp)
target_link_libraries(j3 PRIVATE spdlog EnTT::EnTT d3d11 dxgi d3dcompiler)

target_compile_definitions(j3 PRIVATE UNICODE)
target_compile_definitions(j3 PRIVATE WINDOW_CLASS_NAME=L"j3window")
