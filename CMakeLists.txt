cmake_minimum_required(VERSION 3.20.0)

set(target "ClientServerApplication")
project(${target})

add_compile_options(/Zi /FC /nologo /W4)

set(INCLUDE_DIR code)

set(CMAKE_SUPPRESS_REGENERATION true) # prevent generation of ZERO_CHECK solution

add_executable(${target} ${INCLUDE_DIR}/main.cpp  ${INCLUDE_DIR}/winsock.cpp ${INCLUDE_DIR}/winsock.h)

target_include_directories(${target} PRIVATE ${INCLUDE_DIR})

set_property(TARGET ${target} PROPERTY CXX_STANDARD 17)

target_link_libraries(${target} Ws2_32.lib)