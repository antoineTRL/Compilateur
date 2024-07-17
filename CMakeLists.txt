cmake_minimum_required(VERSION 3.28)
project(Compilateur C)

set(CMAKE_C_STANDARD 11)

add_executable(Compilateur main.c
        lexer.h
        lexer.c
        buffer.h
        buffer.c
        utils.h
        utils.c
        ast.h
        ast.c
        symbol_table.h
        symbol_table.c
        parser.h
        parcer.c
        semantic.h
        semantic.c
        codegen.h
        codegen.c
        print_ast.c
        print_ast.h)
