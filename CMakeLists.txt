cmake_minimum_required(VERSION 3.5)
project(TraderCS4398)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    README.md)

add_executable(TraderCS4398 ${SOURCE_FILES})