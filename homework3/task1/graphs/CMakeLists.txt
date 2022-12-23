cmake_minimum_required(VERSION 3.0.0)
project(graphs)

add_library(${PROJECT_NAME} ListGraph.cpp MatrixGraph.cpp SetGraph.cpp ArcGraph.cpp)

set(GRAPHS_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(GRAPHS_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)