cmake_minimum_required(VERSION 3.14)

project(PAC-MAN)

set(CMAKE_CXX_FLAGS " -std=c++17")
file(GLOB SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
find_package(SFML 2.5 COMPONENTS system window graphics  REQUIRED)
include_directories(include)
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)