cmake_minimum_required(VERSION 3.16)
project(CS499AVLClassPlanner LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(course_planner_core
    AVLTree.cpp
    CourseLoader.cpp
)

target_include_directories(course_planner_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
    target_compile_options(course_planner_core PRIVATE /W4)
else()
    target_compile_options(course_planner_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(course_planner main.cpp)
target_link_libraries(course_planner PRIVATE course_planner_core)

add_executable(course_planner_tests tests/tests.cpp)
target_link_libraries(course_planner_tests PRIVATE course_planner_core)

add_executable(course_planner_comparison performance_demo.cpp)
target_link_libraries(course_planner_comparison PRIVATE course_planner_core)

enable_testing()
add_test(NAME course_planner_tests COMMAND course_planner_tests)
add_test(NAME course_planner_comparison COMMAND course_planner_comparison)
