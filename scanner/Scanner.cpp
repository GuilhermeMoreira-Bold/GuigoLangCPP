//
// Created by guilherme on 07/10/24.
//

#include "Scanner.h"

#include <iostream>

#include "../error/GuigoError.h"

Scanner::Scanner(const std::string &source)  {
    Scanner::source = source;
    keywords.insert({"if",If});
    keywords.insert({"and",And});
    keywords.insert({"if",While});
    keywords.insert({"true",True});
    keywords.insert({"false",False});
    keywords.insert({"and",And});
    keywords.insert({"or",Or});
    keywords.insert({"print",Print});
    keywords.insert({"return",Return});
    keywords.insert({"var",Var});
}


std::list<Token> Scanner::scanTokens() {
    while(!isAtEnd()) {
        start = current;
        scanToken();
    }
    return tokens;
}

bool Scanner::isAtEnd() {
    return current >= source.length();
}

char Scanner::advance() {
    return source.at(current++);
}

void Scanner::addToken(TOKENTYPE type, std::any literal) {
    std::string lexeme = source.substr(start, current - start);
    Token token = Token(type, lexeme, line, literal);
    tokens.push_back(token);
}

void Scanner::addToken(TOKENTYPE token) {
   addToken(token, nullptr);
}


void Scanner::scanToken() {
    if(!isAtEnd()) {
        char c = advance();
        switch(c) {
            case ' ':
            case '\r':
            case '\t':
                break;
            case '\n':
                line++;
                break;
            case '"': string(); break;
            case '(': addToken(LeftParent); break;
            case ')': addToken(RightParent); break;
            case '{': addToken(LeftBrace); break;
            case '}': addToken(RightBrace); break;
            case ',': addToken(Comma); break;
            case '.': addToken(Dot); break;
            case '-': addToken(Minus); break;
            case '+': addToken(Plus); break;
            case ';': addToken(Semicolon); break;
            case '*': addToken(Star); break;
            case '!':
                addToken(match('=') ? BangEqual : Bang); break;
            case '=':
                addToken(match('=') ? EqualEqual : Equal); break;
            case '<':
                addToken(match('=') ? LessEqual : Less); break;
            case '>':
                addToken(match('=') ? GreaterEqual : Greater); break;
            case '/':
                if(match('/')) {
                    while(peek() != '\n' && !isAtEnd()) advance();
                }else {
                    addToken(Slash);
                }
                break;
            default:
                if(isdigit(c)) {
                    number();
                    break;
                }
                if(isalpha(c)) {
                    identifier();
                    break;
                }
               GuigoError::error("Unknown token character", InvalidExpression, line);
                break;
        }
    }

}
char Scanner::peek() {
    if(isAtEnd()) return '\0';
    return source.at(current);
}
void Scanner::string() {
    while(peek() != '"' && !isAtEnd()) {
        if(peek() == '\n') line++;
        advance();
    }

    if(isAtEnd()) {
        GuigoError::error("Unterminated string", InvalidExpression, line);
        return;
    }

    advance();

    std::string value = source.substr(start + 1, current - start - 2);
    addToken(String, value);
}

char Scanner::peekNext() {
    if(current + 1 > source.length()) return '\0';
    return source.at(current + 1);
}

void Scanner::number() {
    while(isdigit(peek())) advance();

    if(peek() == '.' && isdigit(peekNext())) {
        advance();
        while(isdigit(peek())) advance();
    }
    addToken(Number, std::stod(source.substr(start, current)));
}

bool Scanner::isAlphaNumeric(char peek) {
    return isalpha(peek) || isdigit(peek);
}

void Scanner::identifier() {
    while(isAlphaNumeric(peek())) advance();
    std::string value = source.substr(start, current - start);
    auto it = keywords.find(value);
    TOKENTYPE type;

    if(it != keywords.end()) {
        type = it->second;
    }else {
        type = Identifier;
    }
    addToken(type);
}


bool Scanner::match(char expected) {
    if(isAtEnd()) return false;
    if(source[current] != expected) return false;
    current++;
    return true;
}