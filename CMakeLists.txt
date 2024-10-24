cmake_minimum_required(VERSION 3.29)
project(untitled4)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled4 main.cpp
        lexer/TokenType.h
        lexer/Token.cpp
        lexer/Token.h
        error/GuigoErrorCode.h
        scanner/Scanner.cpp
        scanner/Scanner.h
        error/GuigoError.cpp
        error/GuigoError.h
        expressions/ExpressionVisitor.h
        expressions/BinaryExpression.cpp
        expressions/BinaryExpression.h
        expressions/Expression.h
        parser/Parser.cpp
        parser/Parser.h
        expressions/UnaryExpression.h
        expressions/LiteralExpression.h
        expressions/GroupExpression.h
        interpreter/Interpreter.h
        obj/Object.h
)
