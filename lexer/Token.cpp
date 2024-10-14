//
// Created by guilherme on 07/10/24.
//

#include "Token.h"
Token::Token(TOKENTYPE token, std::string lexeme, int line, std::any literal) {
    this->token = token;
    this->lexeme = lexeme;
    this->line = line;

    if(literal.type() == typeid(double)) {
        this->literal = std::any_cast<double>(literal);
    }

    if(literal.type() == typeid(int)) {
        this->literal = std::any_cast<int>(literal);
    }

    if(literal.type() == typeid(std::string)) {
        this->literal = std::any_cast<std::string>(literal);
    }
    
}

std::string Token::toString() {
    return "Token[" + tokenTypeToString(this->token) + ", " + lexeme + "]";
}

