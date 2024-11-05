//
// Created by guilherme on 07/10/24.
//

#include "Token.h"
Token::Token(TOKENTYPE token, std::string lexeme, int line, Object* literal) {
    this->token = token;
    this->lexeme = lexeme;
    this->line = line;
    this->literal = literal;
}

std::string Token::toString() {
    return "Token[" + tokenTypeToString(this->token) + ", " + lexeme + "]";
}

