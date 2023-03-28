cmake_minimum_required (VERSION 3.8)

project (TranStation)
set(CMAKE_CXX_STANDARD 11)
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    string(APPEND CMAKE_CXX_FLAGS  " /source-charset:utf-8")
endif()

include_directories(buffer)
include_directories(src)
include_directories(include)

add_executable(TranServer bin/main.cpp)
add_executable(TranServerTest bin/test.cpp src/trans_buffer.hpp)
