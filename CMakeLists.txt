cmake_minimum_required(VERSION 3.26)
project(Assignment_1_2 C)

set(CMAKE_C_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}"C:/CUnit-2.1-2/CUnit/Headers")
link_directories("C:/CUnit-2.1-2/CUnit/Sources/.libs")

add_executable(Assignment_1_2 main.c)
target_link_libraries(Assignment_1_2 CUnit)