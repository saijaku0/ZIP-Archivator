cmake_minimum_required(VERSION 3.20)

project(HuffmanArchiver VERSION 1.0 LANGUAGES CXX)

# Требуем стандарт C++20 для компиляции.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")


add_executable(archiver
    src/main.cpp
    src/ArchiverCore.cpp
)

target_include_directories(archiver PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
)
