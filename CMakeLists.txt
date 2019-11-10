cmake_minimum_required(VERSION 3.9)
project(algebra-elliptic-curves)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
include_directories("${CMAKE_BINARY_DIR}/src")
set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

file(GLOB SOURCES
		"${PROJECT_SOURCE_DIR}/*.cpp",
		"${PROJECT_SOURCE_DIR}/main.cpp")

add_executable(algebra-elliptic-curves ${SOURCES})
