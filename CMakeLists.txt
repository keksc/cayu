cmake_minimum_required(VERSION 3.28)
project(cayu VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 26)

file(GLOB SRC src/*.cpp lib/*.cpp)

include_directories(include)
add_executable(cayu ${SRC})
