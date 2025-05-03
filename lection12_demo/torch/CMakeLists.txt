cmake_minimum_required (VERSION 3.5)

project(torch_sample VERSION 0.0.1 LANGUAGES CXX)

find_package(Torch REQUIRED)

add_executable( ${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME} torch)
