cmake_minimum_required(VERSION 3.10)
project(Lab3_4 C)

set(CMAKE_C_STANDARD 99)

add_executable(Lab3_4
        sources/main.c
        sources/ui.c
        headers/ui.h
        sources/controller.c
        headers/controller.h
        sources/repository.c
        headers/repository.h
        sources/model.c
        headers/model.h
        sources/vector.c
        headers/vector.h
        )