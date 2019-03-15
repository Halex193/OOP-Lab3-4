cmake_minimum_required(VERSION 3.10)
project(Lab3_4 C)

set(CMAKE_C_STANDARD 99)

file(GLOB hearderFiles "headers/*.h")
file(GLOB sourceFiles "sources/*.c")
file(GLOB testFiles "tests/*")

add_executable(Lab3_4
        main.c
        ${headerFiles}
        ${sourceFiles}
        )
add_executable(Lab3_4-Tests
        ${testFiles}
        ${headerFiles}
        ${sourceFiles}
        )