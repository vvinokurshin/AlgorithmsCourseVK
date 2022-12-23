cmake_minimum_required(VERSION 3.14)
project(task1)

add_subdirectory(graphs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${GRAPHS_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GRAPHS_LIBRARIES})

# tests
enable_testing()
add_subdirectory(tests)