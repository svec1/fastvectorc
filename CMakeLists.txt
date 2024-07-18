cmake_minimum_required(VERSION 3.12)

project(test_m C)

file(GLOB MAIN "src/*.c" "src/*.h")
file(GLOB TEST "test/*.c" "test/*.h")

add_executable(_test ${MAIN})