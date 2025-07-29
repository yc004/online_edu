cmake_minimum_required(VERSION 3.10)
project(online_edu)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB SRC_FILES src/*.cpp)

add_executable(online_edu ${SRC_FILES}) 