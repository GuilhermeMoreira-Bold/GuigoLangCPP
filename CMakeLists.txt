cmake_minimum_required(VERSION 3.29)
project(untitled4)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled4 core/src/main.cpp
        compiler/lexer/TokenType.h
        compiler/lexer/Token.cpp
        compiler/lexer/Token.h
        compiler/error/GuigoErrorCode.h
        compiler/scanner/Scanner.cpp
        compiler/scanner/Scanner.h
        compiler/error/GuigoError.cpp
        compiler/error/GuigoError.h
        compiler/expressions/ExpressionVisitor.h
        compiler/expressions/BinaryExpression.cpp
        compiler/expressions/BinaryExpression.h
        compiler/expressions/Expression.h
        compiler/parser/Parser.cpp
        compiler/parser/Parser.h
        compiler/expressions/UnaryExpression.h
        compiler/expressions/LiteralExpression.h
        compiler/expressions/GroupExpression.h
        compiler/interpreter/Interpreter.h
        compiler/obj/Object.h
)
