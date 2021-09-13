cmake_minimum_required(VERSION 3.20)
project(concise)

set(CMAKE_CXX_STANDARD 20)

add_executable(concise main.cpp syntax/lexer.cpp syntax/lexer.h vm/opcode.h vm/vm.cpp vm/vm.h vm/chunk.cpp vm/chunk.h compiler/value.cpp compiler/value.h)
