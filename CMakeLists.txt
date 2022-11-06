cmake_minimum_required(VERSION 3.2.2)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(RayTracing LANGUAGES CXX)
set(CXX_STANDARD 17)

add_executable(RayTracing src/main.cpp)

target_include_directories(RayTracing PUBLIC include)