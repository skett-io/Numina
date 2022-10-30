cmake_minimum_required(VERSION 3.20)
project(Numina_SDL2)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(SDL2 GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git" GIT_TAG "release-2.24.0")
FetchContent_MakeAvailable(SDL2)

add_library(Numina_SDL2 STATIC Numina_SDL2.cpp)
target_include_directories(Numina_SDL2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(Numina_SDL2 SDL2)
target_compile_options(Numina_SDL2 PUBLIC -fPIC)
