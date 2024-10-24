//
// Created by guilherme on 14/10/24.
//

#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <list>
#include <ostream>

#include "../lexer/Token.h"
#include "../expressions/Expression.h"


class Parser {
public:
    Parser(std::list<Token> &tokens) : tokens(tokens) {};

    Expression* parse() {
        return expression();
    }
private:
    void synchronize();

    int current = 0;
    std::list<Token>& tokens;

    template<typename ...Args>
    bool match(Args... types);
    bool check(TOKENTYPE type);
    bool isAtEnd();



    Token& consume(TOKENTYPE type, std::string message);
    Token& advance();
    Token& peek();
    Token& previous();

    Expression* expression();
    Expression* equality();
    Expression* comparison();
    Expression* term();
    Expression* factor();
    Expression* unary();
    Expression* literal();

};



#endif //PARSER_H
