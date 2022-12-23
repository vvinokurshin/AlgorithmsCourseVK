cmake_minimum_required(VERSION 3.14)
project(test_graphs)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} tests_graphs.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${GRAPHS_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GRAPHS_LIBRARIES} GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})