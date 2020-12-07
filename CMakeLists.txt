cmake_minimum_required(VERSION 3.17)
project(UFP_Alojamentos)

set(CMAKE_CXX_STANDARD 14)

include_directories(scripts)
include_directories(scripts/API)
include_directories(scripts/billing)
include_directories(scripts/data_handler)
include_directories(scripts/general)

add_executable(UFP_Alojamentos
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/Makefile
        cmake-build-debug/UFP_Alojamentos.cbp
        cmake-build-debug/UFP_Alojamentos.exe
        data/agendas/masters/1234_master.psv
        data/agendas/outras/1_outra.psv
        data/agendas/outras/2_outra.psv
        data/agendas/outras_handlers/1234_handler.psv
        data/aloj.csv
        data/edfs.psv
        data/estudio.psv
        data/historico.csv
        data/hospedes.csv
        data/regras_preco.csv
        scripts/API/agendas.c
        scripts/API/agendas.h
        scripts/API/edificios.c
        scripts/API/edificios.h
        scripts/API/guests_list.c
        scripts/API/guests_list.h
        scripts/API/historicoReservas.c
        scripts/API/historicoReservas.h
        scripts/billing/billing.c
        scripts/billing/billing.h
        scripts/data_handler/data_reader.c
        scripts/data_handler/data_reader.h
        scripts/general/project.c
        scripts/general/project.h
        scripts/general/structs.h
        scripts/general/utils.c
        scripts/general/utils.h
        .gitignore
        main.c
        README.md
        TODO.txt)
