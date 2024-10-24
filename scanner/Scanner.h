//
// Created by guilherme on 07/10/24.
//

#ifndef SCANNER_H
#define SCANNER_H
#include <list>
#include <string>
#include <unordered_map>

#include "../lexer/Token.h"

class Scanner {
public:
    std::string source;
    std::list<Token>  tokens;
    std::list<Token> scanTokens();
    bool isAtEnd();

    void string();

    char peekNext();

    void number();
    std::unordered_map<std::string, TOKENTYPE> keywords;
    bool isAlphaNumeric(char peek);

    void identifier();

    void scanToken();
    char advance();
    void addToken(TOKENTYPE token);
    void addToken(TOKENTYPE token, Object* literal);
    bool match(char expected);
    char peek();
    Scanner(const std::string& source);
private:
    int start = 0;
    int current = 0;
    int line = 1;
};



#endif //SCANNER_H
