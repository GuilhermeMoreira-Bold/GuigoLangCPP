//
// Created by guilherme on 07/10/24.
//

#ifndef TOKEN_H
#define TOKEN_H
#include <any>
#include <string>
#include "TokenType.h"
#include "../obj/Object.h"

class Token {
public:
    TOKENTYPE token;
    std::string lexeme;
    int line;
    Object* literal;

    Token(TOKENTYPE token, std::string lexeme, int line, Object* literal);
    std::string toString();
};



#endif //TOKEN_H
