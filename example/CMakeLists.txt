
add_executable(NuminaExample main.cpp)
target_link_libraries(NuminaExample Numina)

add_custom_target(run_example COMMAND NuminaExample)

