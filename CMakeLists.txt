cmake_minimum_required(VERSION 3.10)
project(DataVault)

set(CMAKE_CXX_STANDARD 17)

add_executable(DataVault
    src/main.cpp
    src/Database.cpp
    src/CommandParser.cpp
)


target_include_directories(DataVault PRIVATE inc)
