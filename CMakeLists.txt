cmake_minimum_required(VERSION 3.14)
project(UFP_Alojamentos C)

set(CMAKE_C_STANDARD 99)

add_executable(UFP_Alojamentos main.c scripts/general/project.c scripts/general/project.h scripts/data_handler/data_reader.c scripts/data_handler/data_reader.h scripts/general/utils.h scripts/general/utils.c scripts/API/agendas.c scripts/API/agendas.h scripts/general/structs.h scripts/API/edificios.c scripts/API/edificios.h scripts/billing/billing.c scripts/billing/billing.h scripts/API/guests_list.c scripts/API/guests_list.h)