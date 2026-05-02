cmake_minimum_required(VERSION 3.16)
project(Peechi VERSION 0.1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(peechi
    src/main.cpp
    src/cli/Cli.cpp
    src/core/SourceFile.cpp
    src/diagnostics/PeechiError.cpp
    src/lexer/Token.cpp
    src/lexer/Lexer.cpp
    src/ast/Expr.cpp
    src/ast/Stmt.cpp
    src/parser/Parser.cpp
    src/runtime/Value.cpp
    src/runtime/Environment.cpp
    src/runtime/Interpreter.cpp
)

target_include_directories(peechi PRIVATE include)

if(MSVC)
    target_compile_options(peechi PRIVATE /W4)
else()
    target_compile_options(peechi PRIVATE -Wall -Wextra -pedantic)
endif()
