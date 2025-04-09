cmake_minimum_required(VERSION 3.21)
project(cpp_ca3)

set(CMAKE_CXX_STANDARD 11)

# SFML Setup
set(SFML_STATIC_LIBRARIES FALSE)
set(SFML_DIR "C:/SFML-2.6.2/lib/cmake/SFML")
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
include_directories("C:/SFML-2.6.2/include")

add_executable(cpp_ca3
        src/gui.cpp
        src/Board.cpp
        src/Crawler.cpp
        include/Board.h
        include/Crawler.h
        include/Position.h
)

target_link_libraries(cpp_ca3 sfml-system sfml-window sfml-graphics sfml-audio)


# Set runtime output directory
set_target_properties(cpp_ca3 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Copy SFML DLLs after build, avoids a runtime error and DLL's arent necessary to place in root folder
file(GLOB SFML_DLLS "C:/SFML-2.6.2/bin/*.dll")
file(COPY ${SFML_DLLS} DESTINATION ${CMAKE_BINARY_DIR}/bin)
