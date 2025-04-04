cmake_minimum_required(VERSION 3.30)
project(cpp_ca3)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp_ca3 src/main.cpp
        src/Board.cpp
        include/Board.h
        src/Crawler.cpp
        include/Crawler.h
        include/Position.h
)
