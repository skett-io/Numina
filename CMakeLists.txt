cmake_minimum_required(VERSION 3.20)
project(Numina)

set(CMAKE_CXX_STANDARD 20)

set(NUMINA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(NUMINA_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE NUMINA_SOURCE_FILES ${NUMINA_SOURCE_DIR}/*.c ${NUMINA_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE NUMINA_INCLUDE_FILES ${NUMINA_INCLUDE_DIR}/*.h ${NUMINA_INCLUDE_DIR}/*.hpp)

add_subdirectory(plugins)
add_subdirectory(example)

add_library(Numina SHARED ${NUMINA_SOURCE_FILES} ${NUMINA_INCLUDE_FILES})
target_include_directories(Numina PUBLIC ${NUMINA_INCLUDE_DIR})
target_link_libraries(Numina Numina_SDL2)
