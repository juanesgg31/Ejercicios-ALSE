cmake_minimum_required(VERSION 3.10)

project(casa_inteligente LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(dispositivo
    DispositivoInteligente.cpp
    DispositivoInteligente.h
)

add_executable(simulador
    main.cpp
)

target_link_libraries(simulador
    dispositivo
)
