cmake_minimum_required(VERSION 3.14)
project(UFP_Alojamentos C)

set(CMAKE_C_STANDARD 99)

add_executable(UFP_Alojamentos main.c scripts/project.c scripts/project.h scripts/data_handler.c scripts/data_handler.h scripts/global_defines.h scripts/global_defines.c)