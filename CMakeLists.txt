cmake_minimum_required(VERSION 3.13.4)
project (cork)

include_directories(src)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(cork ${SOURCES})