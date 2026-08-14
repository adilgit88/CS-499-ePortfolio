cmake_minimum_required(VERSION 3.16)
project(CS499CoursePlanner LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(course_planner_core
    BinarySearchTree.cpp
    CourseLoader.cpp
)

target_include_directories(course_planner_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(course_planner main.cpp)
target_link_libraries(course_planner PRIVATE course_planner_core)

add_executable(course_planner_tests tests/tests.cpp)
target_link_libraries(course_planner_tests PRIVATE course_planner_core)

enable_testing()
add_test(NAME course_planner_tests COMMAND course_planner_tests)
