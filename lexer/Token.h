//
// Created by guilherme on 07/10/24.
//

#ifndef TOKEN_H
#define TOKEN_H
#include <any>
#include <string>

#include "TokenType.h"


class Token {
public:
    TOKENTYPE token;
    std::string lexeme;
    int line;
    std::any literal;

    Token(TOKENTYPE token, std::string lexeme, int line, std::any literal);

    std::string toString();
private:


};



#endif //TOKEN_H
