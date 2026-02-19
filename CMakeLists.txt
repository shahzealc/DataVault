cmake_minimum_required(VERSION 3.10)
project(InMemoryDatabaseEngine)

set(CMAKE_CXX_STANDARD 17)

add_executable(InMemoryDatabaseEngine
    src/main.cpp
    src/Database.cpp
    src/CommandParser.cpp
)


target_include_directories(InMemoryDatabaseEngine PRIVATE inc)
