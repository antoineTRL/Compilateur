cmake_minimum_required(VERSION 3.28)
project(Compilateur C)

set(CMAKE_C_STANDARD 11)

add_executable(Compilateur main.c
        lexer.h
        lexer.c
        buffer.c
        utils.c
        ast.c
        new_unary.c)
